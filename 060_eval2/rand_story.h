#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
void parseFile(const char * file, catarray_t * cats, int noreuse);
void stripNewLine(char * str);
catarray_t * catClassifier(char * file);
char * getWordFromBackref(char * ref, category_t * usedWords);
void filter(catarray_t * cats, category_t * usedWords);
void freeCatArray(catarray_t * cats);
#endif
