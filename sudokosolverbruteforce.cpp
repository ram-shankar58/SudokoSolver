//SOlving a 9x9 sudoko using Backtracking method
/* WE can fill the spaces using numbers 1-9. 
A number 0 represents an empty space*/

#include <iostream>
using namespace std;

void print(int grid[9][9]){
    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl; //to send every row to the next line

    }
}

void getvalues(int arr[9][9]){
    //no need int arr[9][9]={0}; //initialising everything to 0
    cout<<"Do you want to initialise values? type y or n"<<endl;
    char ans;
    cin>>ans;
    if (ans=='y'){
        cout<<"PRInt the value for each of the position elements"<<endl;
        for( int i=1; i<=9; i++){
            for (int j=1; j<=9; j++){
                cout<<"ENter value for row"<<i<<" and column"<<j<<endl;
                cin>>arr[i-1][j-1];
            }
        }
    }
}
//this function gets the values from the user. IF not, the default value is initialised to 0.

bool checking(int arr[9][9], int num, int row, int col){
    //checks if it is correct to assign a number to a space
    for (int i=0; i<9; i++){
        if (arr[row][i]==num){
            return false;
        }
    }
    for (int i=0; i<9; i++){
        if (arr[i][col]==num){
            return false;
        }
    }
    //we have checked the row and the column for the corresponding element
    //now we have to check if the particular grid is sattisfied
    //since also a 3x3 grid must be sattisfied too
    //we have 9 3x3 grids. WE first find out which grid the given element belongs to.
    int startrow=3*(int((row)/3)); //starting index of the corresponding 3x3 grid
    int startcolumn=3*(int((col)/3)); 
    for (int i=startrow;i<startrow+3;i++){
        for (int j=startcolumn;j<startcolumn+3;j++){
            if (arr[i][j]==num){
                return false; //found a duplicate in the corresponding 3x3 smaller grid
            }
        }
    }
    return true;

}
/* NOw comes the most important part
HEre we are going to fill the remaining of the partially filled spaces
WE attempt to assign values to the empty parts
*/
//we use backtracking. THe recursive function is of bool return type as it proceeds only if we get the outcome to be true
//If outcome is false, the recursion stops there and the next value is applied
//HEnce this method is backtracking.

bool filling(int arr[9][9], int row, int col){
    //before starting out the main filling part, we code the constraints
    if (row ==8 && col==9){ //we type col as 9 here because we return true after the last element of the row also has been filled
        return true; //row=8 and col=8 is the last element. After we fill the last element, we return true

    }
//to avoid further backtracking
    if (col==9){ //after we fill the last column of a given row
        row++;
        col=0;
    }// if we reach end of the col, we go to next row
    //now we start filling the values

    //we need to check if the current cell is already filled.
    //checking if current cell is already filled
    if (arr[row][col]!=0){
        //means this cell is already filled. So we go to next cell
        return filling(arr, row, col+1); //we check the next column
    }
    
    //if the cell is empty, we go forward to fill it

    for (int num=1; num<=9; num++){
        if (checking(arr, num,row, col)){
            arr[row][col]=num; //if it suits, we equate the value
            //we call the function recursively here itself since if we do so, if the fuction
            //returns false, we would have to backtrack and change another number to try upon
            if(filling(arr, row, col+1)){
                return true;
            }
            
        }
        else{
                arr[row][col]=0;
        }
    }
    //return false;
    return false;
}
//we have defined everything correctly and successfully.
int main(){
    int grid[9][9]={0};
    getvalues(grid);
    //n=we have initialised everything to 0 (As empty), and now have gotten the valeus from the user
    //now we start filling everything
    if(filling(grid, 0, 0)){
        cout<<"SOlved succesfully!"<<endl;
        print(grid);
    }
    else{
        cout<<"NO possible values for this"<<endl;
    }
    return 0;
}
