/* global definitions file*/

#ifndef GL_DEFS_H
#define GL_DEFS_H

#include <utility>
#include <limits.h>

using namespace std;

typedef unsigned int WordIndex;
typedef unsigned int PositionIndex;
const unsigned int MAX_VOCAB_SIZE = UINT_MAX;
const int TRAIN_BUFFER_SIZE = 500000;
const unsigned int MAX_SENTENCE_LENGTH = 300;
const long long G1 = MAX_SENTENCE_LENGTH + 5;
const long long G2 = G1*G1, G3 = G2*G1;
const int MAX_W = 460000;
typedef pair<WordIndex, WordIndex> WordPairIds;

#endif
