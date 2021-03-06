#include "simple_tree.h"

using namespace std;


Simple_tree::Simple_tree(){

}

Simple_tree::Simple_tree(string str, llu f)
	:hd(str),
	freq(f),
	sons_tot(0)
{}

Simple_tree::~Simple_tree(){
	long long int n = sons.size();
	for (long long int i = 0; i < n; i++){
		delete sons[i];
	}
}

void Simple_tree::read_from_file(istream* ifs){
	string buff_word;
	llu buff_f, n;

	(*ifs) >> buff_f;
	sons_tot = buff_f;

	(*ifs) >> n;
	for (llu i = 0; i < n; i++){
		sons.push_back(new Simple_tree());
		// Fill son informations
		(*ifs) >> buff_word;
		sons[i]->hd = buff_word;
		(*ifs) >> buff_f;
		sons[i]->freq = buff_f;
		sons[i]->read_from_file(ifs);
	}
}

void Simple_tree::write_to_file(FILE* f){
	fprintf(f, "%llu\n%llu\n", sons_tot, sons.size());
	for (Simple_tree* s : sons){
		fprintf(f, "%s %llu\n", s->hd.c_str(), s->freq);
		s->write_to_file(f);
	}
}

void print_rec(ostream* ofs, Simple_tree* t, string prefix){
	(*ofs) << prefix << "-(" << t->hd << " " << t->freq << ")" << endl;
	prefix.append(" |");
	for (llu i = 0; i<(t->sons).size(); i++){
		if (i == (t->sons).size() - 1)
			prefix[prefix.length() - 1] = ' ';

		print_rec(ofs, t->sons[i], prefix);
	}
}

void Simple_tree::print(ostream* ofs){
	(*ofs) << "(" << hd << " " << freq << ")" << endl;
	string prefix = "|";
	for (llu i = 0; i<(sons).size(); i++){
		if (i == (sons).size() - 1)
			prefix = " ";

		print_rec(ofs, sons[i], prefix);
	}
}

void Simple_tree::add(queue<string> seq,llu f){
	bool exists = false;
	llu i = 0;
	string w = seq.front();
	while (!exists && i < sons.size()){
		exists = (sons[i]->hd == w) || exists;
		i++;
	}
	if (exists){
		i--;
	}
	else{
		sons.push_back(new Simple_tree(w, 0));
	}

	sons[i]->freq += f;
	seq.pop();
	sons_tot += f;
	if (!seq.empty())
		sons[i]->add(seq, f);

}

bool Simple_tree::is_in(queue<string> seq){
	if (seq.empty()) return true;
	bool ret = true;
	for (Simple_tree* s : sons){
		if (s->hd == seq.front()){
			seq.pop();
			ret = ret && s->is_in(seq);
			return ret;
		}
	}
	return false;

}

llu Simple_tree::get(queue<string> seq){
	for (Simple_tree* s : sons){
		if (s->hd == seq.front()){
			seq.pop();
			if (seq.empty()){
				return s->freq;
			}
			else{
				return s->get(seq);
			}
		}
	}
	return 0;
}

double Simple_tree::get_p(queue<string> seq){
	for (Simple_tree* s : sons){
		if (s->hd == seq.front()){
			seq.pop();
			if (seq.empty()){
				cout << (double)s->freq << " " << (double)sons_tot << endl;
				return ((double)s->freq) / ((double)sons_tot);
			}
			else{
				return s->get_p(seq);
			}
		}
	}
	return 0;
}

string Simple_tree::get_rand(queue<string> prev){

	if (prev.empty()){
		if (sons.size() == 0) return "";
		llu r = (rand() / (double)RAND_MAX)*((double)sons_tot);
		llu h = 0, i = 0;
		while (r >= h && i < sons.size()){
			h += sons[i]->freq;
			i++;
		}
		return sons[i - 1]->hd;

	}

	string str = prev.front();
	prev.pop();

	for (llu i = 0; i < sons.size(); i++){

		if (sons[i]->hd == str) return sons[i]->get_rand(prev);
	}


	return "";
}

double Simple_tree::entropy(int order){
	double ret = 0.0;
	double p;
	if (order == 0){

		for (Simple_tree* s : sons){
			p = ((double)(s->freq)) / ((double)sons_tot);
			ret += p * (log(p) / log(2.0));
		}
		return (-ret);
	}
	else{
		for (Simple_tree* s : sons){
			p = ((double)(s->freq)) / ((double)sons_tot);
			ret += p * s->entropy(order - 1);
		}

		return ret;
	}
}

