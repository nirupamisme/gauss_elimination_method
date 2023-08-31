// Author: Nirupam Pal
// Date: 17/08/2023
// Description: This program is used for solving linear equations using gaussian elimination method

#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;

// Function for back-substitution
float *backward_substitution(int n, float **matrix) {
    float *sol = new float[n];

    for (int i = n-1; i >= 0; i--) {
        sol[i] = matrix[i][n];
        // for (int j = i+1; j < n; j++) {
        for (int j = n-1; j > i; j--) {
            sol[i] = sol[i] - matrix[i][j] * sol[j];
        }
        sol[i] = sol[i] / matrix[i][i];
    }
    return sol;
}

// Function for forward elimination
float **forward_elimination(int n, float *aug_mat) {
    float **elim_matrix = new float*[n];

    for (int i = 0; i < n; i++) {
        elim_matrix[i] = new float[n+1]; 
        for (int j = 0; j < n+1; j++) {
            elim_matrix[i][j] = *(aug_mat+i*(n+1)+j);
        }
    }

    // Using the partial pivoting for the augmented matrix
    int pivot_row = 0;             
    for (int j = 1; j < n; j++) {
        if (abs(elim_matrix[pivot_row][pivot_row]) < abs(elim_matrix[j][pivot_row])) {
            for (int k = 0; k < n+1; k++) {
                float d = elim_matrix[pivot_row][k];
                elim_matrix[pivot_row][k] = elim_matrix[j][k];
                elim_matrix[j][k] = d;
            }
        }
    }

    // Performing the gaussian elimination
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            float piv = elim_matrix[j][i] / elim_matrix[i][i];
            for (int k = 0; k < n+1; k++) {
                elim_matrix[j][k] = elim_matrix[j][k] - piv * elim_matrix[i][k];
            }
        }
    }
    return elim_matrix;
}

int main() {
    
    cout << "*-----------------------------------------*-----------------------------------------*" << endl;
    cout << "|                                 Author: Nirupam Pal                               |" << endl;
    cout << "|                                   Date: 17/08/2023                                |" << endl;
    cout << "|This program is used for solving linear equations using gaussian elimination method|" << endl;
    cout << "*-----------------------------------------*---------------------------------------- *" << endl;
    
    int n;

    cout << "\nEnter the number of equations to be solved: ";        
    cin >> n;

    float aug_matrix[n][n+1], *mat, values[n*(n+1)];
    mat = &aug_matrix[0][0];

    // Entering the equations using the file data.txt
    ifstream myfile("./data.txt");
    float a;
    int l = 0;
    while (myfile >> a) {
        values[l] = a;
        l++;
    }
    myfile.close();
    for (int i = 0; i < n*(n+1); i++) {
        *(mat+i) = values[i];
    }

    // Calling the function for gaussian elimination
    float **new_matrix = forward_elimination(n, &aug_matrix[0][0]);

    // Calling the function for backward substitution
    float *sol = backward_substitution(n, new_matrix);

    // Create and open a new text file
    ofstream MyFile("./solution_file_2.txt");

    // Printing the results after back-substitution
    cout << "\nThe value of unknowns for the above equations are :" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i+1 << " : " << sol[i] << endl;
        // Write the solution to the file
        MyFile <<  "X" << i+1 << " : " << sol[i] << endl; 
    }

    // Close the file for the output
    MyFile.close();
      
    return 0;
}