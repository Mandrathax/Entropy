#include "store.h"

Store::Store(){}
Store::~Store(){}

void Store::open(char* filename){}
void Store::close(char* filename){}

bool Store::is_init(){ return false; }
void Store::init(){}

bool Store::exists(queue<string> seq){ return false; }
void Store::create(queue<string> seq, llu nb){}

llu Store::get_hits(queue<string> seq){ return 0; }
void Store::add_hits(queue<string> seq, llu nb){}

double Store::get_proba(queue<string> seq){ return 0.0; }
string Store::next(queue<string> seq){ return ""; }

double Store::entropy(int order){ return 0; }
