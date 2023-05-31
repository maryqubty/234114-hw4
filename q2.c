#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N (100)
#define MAX_LEN (255)
#define MAX_SENTENCE_LEN ((MAX_LEN + 1) * N - 1)
#define WORD_SEPERATOR ('_')
#define SUCCESS (0)
#define ERROR (1)


/*this function asks the user for a
 value to put it in the n ,
 it returns false if the value is not legal*/
bool read_number_of_strings(int * n) {
    if (scanf("%d", n) != 1) {
        return false;
    }

    return ((*n >= 1) && (*n <= N));
}
/*this function receives an array of strings and frees them */
void free_strings(char * strings[], int n) {

    for(int i=0; i<n;i++)
    {
        free(strings[i]);
    }
}

///////////////////////////////////////
/*this function copies the string  */
void copy_string(char * check,char string_array[])
{
    while(*string_array)
    {
        *check=*string_array;
        check++;
        string_array++;
    }

}
///////////////////////////////////////
/*this function gets sentences from the user
and puts them in the main array ,
 the function uses malloc to point at the sentence*/
bool read_strings(char * strings[], int n) {


for(int i=0;i<n;i++)
{

char string_array[MAX_LEN];
scanf("%s",string_array);
int size =strlen(string_array);

char * check = (char *)malloc((size+1) * sizeof(char));
if(check==NULL){return false;}

copy_string(check,string_array);
check[size]=0;
strings[i]= check ;

}

return true ;



}
//////////////////////////////////////////////////////////////////
/*this function turns the small letter
 into capital letter and returns it */
char upCase(char c)
 {
if (c >= 'a' && c <= 'z')
    {
return c - 'a' + 'A';
    }
return c;
 }

///////////////////////////////////////
/*this function compares between two strings
 in insensitive way and returns
0 if the two are alike, returns minus
if the first strings comes after
the second string according to the
 ascii table ,and plus otherwise */
int insensitive_compare(char *str1, char *str2)
{
    while (*str1 && *str2 && (upCase(*str1)== upCase(*str2)) ){
        str1++;
        str2++;
    }
    return ((int)(upCase(*str1)) - (int)(upCase(*str2)));
}
////////////////////////////////////////////////////////////////////
/*this function checks if the array is sorted in ascending
 order and insensitive way according to ascii table */
bool are_sorted(char * strings[], int n) {

if(n==1){return true;}
 for(int i=0 ; i<n-1;i++)
 {
   int check = insensitive_compare(strings[i], strings[i+1]);
   if(check>0){return false;}
 }
 return true;
}
/*this function checks if the string is in the arrays of the strings */
bool is_string_in_array(char * strings[], int n, char * string) {

    int low =0 ;int high=n-1;
    while (low<=high)
    {
        int check_high = insensitive_compare(strings[high],string);
            if(check_high==0){return true;}
            else if (check_high<0){return false;}
            high --;
            int check_low = insensitive_compare(strings[low],string);
            if(check_low==0){return true;}
            else if (check_low>0){return false;}
            low++;

    }
    return false ;
}
/*this function mashes between tow arrays */
void mash_arrays(char* pointer1, char* pointer2)
{
    if(*pointer2=='\0')
        if(*(pointer1-1)=='_')
        {
            *(pointer1-1)=0;
            return;
        }

    char *str12 = pointer1;
    char *str13 = pointer2+1;
    while (*str13 != '\0') {
    *str12 = * str13;
    str12++;
    str13++;
                         }
    while (*str12 != '\0')
        {
        *str12=0;
        str12++;
        }
}

/*this is the main function which recieves a
 sentence and check if it has any unwanted
 words according to the table and deletes
 them accordingly from the sentence*/
void delete_words(char * words[], int n, char * sentence) {


   char * pointer1=sentence;
   char * pointer2=sentence;

   while( *pointer1)
   {
       while(*pointer1=='_')
       {pointer1++;}
       while(*pointer2=='_')
       {pointer2++;}

       while( *pointer2 && *pointer2!='_')
        {pointer2++;}

       int word_size=strlen(pointer1)-strlen(pointer2);
       char * helper=(char *)malloc((word_size+1)*sizeof (char));

       for(int i=0;i<word_size;i++)
       {
           helper[i]= *(pointer1+i);
       }
        helper[word_size]=0 ;

       if(!is_string_in_array(words,n,helper))
        {
            pointer1=pointer2;
        }
        else {mash_arrays(pointer1,pointer2);
                pointer2=pointer1;}

                free(helper);

}
}

int main() {
    int n;
    printf("Enter number of banned words: ");
    if (!read_number_of_strings(&n)) {
        printf("Invalid number!\n");
        return ERROR;
    }

    char * banned_words[N];
    printf("Enter banned words: ");
    if (!read_strings(banned_words, n)) {
        printf("Can't read words!\n");
        return ERROR;
    }

    if (!are_sorted(banned_words, n)) {
        printf("Words are not sorted correctly!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    char sentence[MAX_SENTENCE_LEN + 1];
    printf("Enter a sentence:\n");
    if (scanf("%s", sentence) != 1) {
        printf("Invalid sentence!\n");
        free_strings(banned_words, n);
        return ERROR;
    }

    delete_words(banned_words, n, sentence);
    printf("Censored sentence:\n%s\n", sentence);

    free_strings(banned_words, n);
    return SUCCESS;
}
