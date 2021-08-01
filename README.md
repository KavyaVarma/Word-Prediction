# Word Prediction
A **trie** based program that can autosuggest and autocorrect words based on a given input.

## Features
##### Autosuggest
The program predicts the possible word based on the partial word typed so far. The possible suggestions are ordered by most likely to least based on the frequency of the word.

##### Autocorrect
The program suggest possible corrections to words typed by into account the following error scenarios:
- Words with extra erroneous letters
- Words with flipped letters

## Compilation
```
cd src
gcc -c wordSuggest.c
gcc wordTree.c wordSuggest.o -o wordPrediction.out
./wordPrediction.out
```

## Sample Usage
```
$ ./wordPrediction.out
Successfully created tree!
>> godo
godown godowns good goo 
>> cabel
cable abel cabeliau cabellerote 
>> watre
water ware 
>> clairvo
clairvoyance clairvoyances clairvoyancies clairvoyancy clairvoyant clairvoyantly clairvoyants 
```
