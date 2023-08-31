// Author: Nirupam Pal
// Date: 17/08/2023
// Description: This program is used for solving linear equations using gaussian elimination method

#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;

int main()
{
    cout << "*-----------------------------------------*-----------------------------------------*" << endl;
    cout << "|                                 Author: Nirupam Pal                               |" << endl;
    cout << "|                                   Date: 17/08/2023                                |" << endl;
    cout << "|This program is used for solving linear equations using gaussian elimination method|" << endl;
    cout << "*-----------------------------------------*---------------------------------------- *" << endl;

    int n;
    
    cout << "\nEnter the number of equations to be solved: ";        
    cin >> n;

    double aug_matrix[n][n+1], sol[n];

    // // Entering the predefined augmented matrix
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n+1; j++) {
    //         if (j < n) {
    //             aug_matrix[i][j] = max(i+1, j+1);
    //         }
    //         else {
    //             aug_matrix[i][j] = 1;
    //         }
    //     }  
    // }
    
    // Entering the augmented matrix manulally
    cout << "Enter the elements for the augmented matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n+1; j++) {
            cout << "A|B[" << i+1 << "][" << j+1 << "] : ";
            cin >> aug_matrix[i][j]; 
        }    
    }

    // Printing the augmented matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n+1; j++) {
            cout << aug_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Using the partial pivoting for the augmented matrix
    int pivot_row = 0;             
    for (int j = 1; j < n; j++) {
        if (abs(aug_matrix[pivot_row][pivot_row]) < abs(aug_matrix[j][pivot_row])) {
            for (int k = 0; k < n+1; k++) {
                float d = aug_matrix[pivot_row][k];
                aug_matrix[pivot_row][k] = aug_matrix[j][k];
                aug_matrix[j][k] = d;
            }
        }
    }

    // Performing the gaussian elimination
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            double piv = aug_matrix[j][i] / aug_matrix[i][i];
            for (int k = 0; k < n+1; k++) {
                aug_matrix[j][k] -= piv * aug_matrix[i][k];
            }
        }
    }

    // Performing the back substitution for obtaining the solution
    for (int i = n-1; i >= 0; i--) {                     
        sol[i] = aug_matrix[i][n];
        for (int j = i+1; j < n; j++) {
            sol[i] -= aug_matrix[i][j] * sol[j];
        }
        sol[i] = sol[i] / aug_matrix[i][i];
    }

    // Create and open a new text file
    ofstream MyFile("./solution_file.txt");

    // Printing the results after the back substitution
    cout << "\nThe solution for the equations are: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i+1 << " : " << sol[i] << endl;
        // Write the solution to the file
        MyFile <<  "X" << i+1 << " : " << sol[i] << endl; 
    }

    // Close the file for the output
    MyFile.close();

    return 0;
}