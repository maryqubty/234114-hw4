#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define EPS (1e-6)
#define N (100)
#define M (100)
#define SUCCESS (0)
#define ERROR (1)
#define ONE_ROW 1
#define two_inputs 2


double zero_by_threshold(double num, double eps) {
    return fabs(num) > eps ? num : 0;
}

bool read_sizes(int * n, int * m) {
    if (scanf("%d%d", n, m) != two_inputs) {
        return false;
    }

    return ((*n >= 1) && (*n <= N) && (*m >= 1) && (*m <= M));
}

void print_matrix(double a[][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%.2f ", zero_by_threshold(a[i][j], EPS));
        }

        printf("\n");
    }

    printf("\n");
}

bool read_matrix(double a[][M], int n, int m) {

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
    {
        double value=0;
        int check =scanf("%lf",&value);

        if(check!=1){return false;}
        a[i][j]=value;

    }
    return true;
}


/*this function swaps between rows accordingly */
void swap_rows(double a[][M], int m, int row1, int row2) {
    double help_array[m];

    for (int j=0; j<m;j++)
    {
        help_array[j]=a[row1][j];
    }

    for(int j=0;j<m;j++)
    {
        a[row1][j]=a[row2][j];
        a[row2][j]=help_array[j];
    }

}
/*this function multiply each value in the row with a scalar*/
void multiply_row(double a[][M], int m, int row, double scalar) {

    for(int j=0;j<m;j++)
    {
        a[row][j]*=scalar ;

    }
}
/*this function adds row multiplied with a scalar to another row*/
void add_row_to_row(double a[][M], int m, int row1, int row2, double scalar) {
    for(int j=0; j<m;j++)
    {
        double value = a[row2][j];
       a[row1][j]+=value*scalar ;
    }
}
//////////////////////////////////////////////////////////////////
/*this function gets the index of column lead in the matrix  */
int get_column_lead(double a[][M], int n, int m)
{     int stop=0;
    int column_lead=m ;
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<m&&!stop;j++)
    {


        if(zero_by_threshold(a[i][j], EPS)!=0)
            {if(j<column_lead)
             column_lead=j;
             stop=1;



            }
    }
    stop=0;
    }
    return column_lead ;

}
/////////////////////////////////////////////////////////////////
/*this function gets the index of row lead in the matrix  */
int get_row_lead(double a[][M], int n, int column_lead)
{
   for(int i=0 ; i<n ;i++)
   {
       if(zero_by_threshold(a[i][column_lead], EPS)!=0)
       {
           return i;
       }
   }
   return 0;
}


/////////////////////////////////////////////////////////////////////
/*this function calls to other functions to help get
the values of the lead rows and columns in
the matrix , the function return
 false if the matrix is 0*/
bool find_leading_element(double a[][M], int n, int m, int * row, int * column)
 {

    int column_lead= get_column_lead(a,n,m);
    if(column_lead==m)return false;

    int row_lead=get_row_lead(a,n,column_lead);
    *row =row_lead;
    *column=column_lead;

    return true;

}

/*this function is the main function , it calls the
 other functions in order to
  reduce rows accordingly */
void reduce_rows(double a[][M], int n, int m) {
    bool check = true;

    int row;
    int column;

    int pointer = 0;
    int i=0;
    check = find_leading_element(a+pointer,n,m,&row,&column);
    while(check && i<n)

    {

                swap_rows(a+pointer,m,0,row) ;

           double scalar = (double)1/(a[pointer][column]);
           multiply_row(a,m,i,scalar);

           for(int j=i+1;j<n;j++)
           {

                if(zero_by_threshold(a[j][column], EPS)==0){continue;}

               scalar=-1*(a[j][column]);
               add_row_to_row(a,m,j,i,scalar);
           }

           i++;
           if(i!=n)
                {
           pointer++;
           check = find_leading_element(a+pointer,n-pointer,m,&row, &column);
                }
    }
}

int main() {

    int n;
    int m;
    printf("Enter matrix size (row and column numbers): ");
    if (!read_sizes(&n, &m)) {
        printf("Invalid sizes!\n");
        return ERROR;
    }

    int a[N][M];
    printf("Enter matrix:\n");
    if (!read_matrix((double (*)[M]) a, n, m)) {
        printf("Invalid matrix!\n");
        return ERROR;
    }

    reduce_rows((double (*)[M]) a, n, m);
    printf("The reduced matrix:\n");
    print_matrix((double (*)[M]) a, n, m);
    return SUCCESS;
}
