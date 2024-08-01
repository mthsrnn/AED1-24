#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RemoveTwoCharacters( int index, char *source ) {
	int remainingBytesOfS = strlen( source ) - index - 1; // quero copiar o '/0'
	memmove( source + index, source + index + 2, remainingBytesOfS );
}

int maximumGain( char *s, int x, int y ) {
	int score = 0, i, j = 0;
	char *localCopy = ( char * )malloc( sizeof( char ) * ( strlen( s ) + 1 ) );

	strcpy( localCopy, s );

	if( x > y ) {


		while( j < strlen( localCopy ) ) {
			while( i < strlen( localCopy ) ) {
				if( localCopy[i] == 'b' && localCopy[i + 1] == 'a' ) {
					RemoveTwoCharacters( i, localCopy );
					score += y;
					i = 0;
					continue;
				}

				i++;
			}

			if( localCopy[j] == 'a' && localCopy[j + 1] == 'b' ) {
				RemoveTwoCharacters( j, localCopy );
				score += x;
				j = 0;
				continue;
			}

			j++;
		}
        return score;

	} else {

		while( j < strlen( localCopy ) ) {
			while( i < strlen( localCopy ) ) {
				if( localCopy[i] == 'b' && localCopy[i + 1] == 'a' ) {
					RemoveTwoCharacters( i, localCopy );
					score += y;
					i = 0;
					continue;
				}

				i++;
			}

			if( localCopy[j] == 'a' && localCopy[j + 1] == 'b' ) {
				RemoveTwoCharacters( j, localCopy );
				score += x;
				j = 0;
				continue;
			}

			j++;
		}
	}

	return score;
}

int main( void ) {
	char *s =
	    "azbauaasbbbpuaabbaabwbababyabafabsauofaaaayaabaaaaubbababaaabxaaaoyeaaaa"
	    "bbbhbqaqbaavababbbahbbhxdbaaanjbbtbbbiaabkakbbaaawbbbambbbwaagabbbbabaai"
	    "bbababbbbarbabbkainbbabaaarbznwaaarapababaebababzyabaabbbaqbabrftbbbauaa"
	    "fnabaabkbraanbiabbbbabbasdaabnbaaaaaabbfabbgbaabbababbbbbnunaaabyavabgab"
	    "bbeidbaahbbabybsbbabhaksdaaabtaabasxfababbapaskfbbaaavhfbapbabjxabqadgbb"
	    "babbbibcbabaaagbbvaabahbbbkamlabubbananbabbaababbbbbbbbbbaqbbqabfabribaj"
	    "bbbaaamlbbbbbaaaabpabcqabppbaabtlbuuugbiabakabaaazebababbbbaaaabbhqbabbb"
	    "abatbazbbrbbiabbbabbabbbaafvbabaaababraczbbaakbabbbaacajbarglzaabjbbbafn"
	    "aabaadbratbeybbbaaababepcbbbyabbbtabypababbqbaaaiqasgqabtbbvalaaaaibbiag"
	    "bbhfbbbbaabaepbauaxaababaabbobaahhamahaababuaaaabaarlbaaaaamaavbwaabaqbs"
	    "apaaaxbabaaabbboaaabaabozacavabamaaaasbaaiaabbsaebybisvbaabbbbaagaaaeaaa"
	    "aabybabbabbacbbbbabtbaahzabmxbkfnbbcbaaalabtabbbbbbbbplbsbdbabgabaabbbaa"
	    "qabjsaabbbobaarbatzabbxbgabuabaaqaababbbabvggnabbaazbabababfbbbabsbuaaba"
	    "stbbbbbabmbkbabbbvvybbabqbjbabgbbbaaaezzuadwmbababaacodaabafpbbabbzybajb"
	    "awaacabibaabaaebjblabbgaabbabbbbxbabribaaaawbbaaaabaabbunraaaasbbiaaabye"
	    "gobbranejadagbdaabbbkxaabbaaaabqbbbanaaalbbbbaaagaafaaaaaaacababcbaoaabb"
	    "ibaancbbaabaabaabbaareaabbssobabavsgbaaabbbbaaubbaaabbabbbxoaabbbpdbbabb"
	    "boaavaaebaabbhajeasbbtacbabbaabbbabablpbbaapaczaabbaggobskbabbwaabobaaaa"
	    "abnpbahasbababxabbdraamqbababbtbbaaaaixaaababbbzbayababybuabbaablabbabaa"
	    "ababwabaabbavbsbbbbaajuaabbbbtbobbblbbbbzbabbbbbsbgbbabbsablasbbbbbxbabi"
	    "cbdbabtbbbaabacgaabaarabaaabbbbaaabaqatabhbhjbbabbaaqfaambuaaknbfabbbaaa"
	    "oaabaababababbuaababaaafabbababababbadbbabuaawfbztabbaonltbaataaaapbaatz"
	    "aaaaybbananevaabaabxsabbbaabkabbbjaakbaazzbbcbbbbs";

	int score = maximumGain( s, 3605, 192 );

	printf( "%d\n", score );

	return EXIT_SUCCESS;
}
