/*
* tvm:  Time Value of Money
*
* Assignment 2 of CSE 13S, Spring 2026.
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Three filestreams by default:
// 0: stdin (standard input) (connected to terminal tty)
// 1: stdout (standard output)
// 2: stderr (reserved for standard error messages)



/*
* The financial calculator's variables:
*/
double N, I, PV, PMT, FV;
// Consider our global variables

/*
* Purpose:      Function f(N) used by the Newton-Raphson root finder.
*
* Parameter:    Number of periods N.
*
*               See equation (7) in the assignment PDF.  For all
*               values except for N, use the global variables.  For N,
*               use the value of the parameter.
*
* Returns:      f' (N)
*/
double fN(double N) {
    double x = pow( 1 + I, -N);
    return PV + PMT * ((1 - x) / I) + FV * x; 
}


/*
* Purpose:      Function f(I) used by the Newton-Raphson root finder.
*
* Parameter:    Interest rate I.
*
*               See equation (12) in the assignment PDF.  For all
*               values except for I, use the global variables.  For I,
*               use the value of the parameter.
*
* Returns:      f' (I)
*/
double fI(double I) {
    double x = pow(1 + I, -N);
    return PV + PMT * ((1 - x) / I) + FV * x;
}


/*
* Purpose:      Function f'(N) used by the Newton-Raphson root finder.
*
* Parameter:    Number of periods N.
*
*               See equation (8) in the assignment PDF.  For all
*               values except for N, use the global variables.  For N,
*               use the value of the parameter.
*
* Returns:      f' (N)
*/
double fN_prime(double N) {
    double x = pow(1 + I, N);
    double y = log(1 + I);
    return y * (PV + (PMT / I)) * x;
}


/*
* Purpose:      Function f'(I) used by the Newton-Raphson root finder.
*
* Parameter:    Interest rate I.
*
*               See equation (13) in the assignment PDF.  For all
*               values except for I, use the global variables.  For I,
*               use the value of the parameter.
*
* Returns:      f' (I)
*/
double fI_prime(double I) {
    double x = pow(1 + I, N);
    double y = pow(1 + I, N - 1);
    return N * (PV + (PMT/ I)) * y - PMT * ((x + 1) / pow(I,2));
}


/*
* Purpose:      Find N such that fN(N) == 0 using a simple Newton-Raphson
*               root finder.
*
*               Use the pseudocode in section 6.2 of the assignment PDF
*               along with equations (7), (8), and (9).
*
* Parameters:   line_number for error messages.
*
* Returns:      N such that fN(N) == 0.
*/
double newton_raphson_N(int line_number) {
   double initial_N = 360;
    // delta for the loop
    double delta = 0;
    int k;
    for (int k = 0; k <= 10000 ; ++k) {
        delta = -fN(initial_N) / fN_prime(initial_N);
        if (delta == 0.0 || isnan(delta)) {
            break;
        }
        initial_N = initial_N + delta;
        //delta = -pv + pmt * ((1 - x / i)) + fv * x / log(y) * ((pv + pmt / i)) * y;
        if (fabs(delta) <  1e-8) 
            break; 
    }    
    if (fabs(delta) >= 1e-8) {
            fprintf(stderr,"line %d: solver did not converge \n", line_number);
            exit(1);
            
    }

    
    return N = ceil(initial_N); 
}


/*
* Purpose:      Find I such that fI(I) == 0 using a simple Newton-Raphson
*               root finder.
*
*               Use the pseudocode in section 6.3 of the assignment PDF
*               along with equations (12), (13), and (14).
*
* Parameters:   line_number for error messages.
*
* Returns:      I such that fI(I) == 0.
*/
double newton_raphson_I(int line_number) {
    double current_I = 0.0025;
    // Our Delta
    double delta = 0;
    int k;
    for (int k = 0; k <= 10000; ++k) {
        delta = -fI(current_I) / fI_prime(current_I);
       current_I = current_I + delta;
        if (fabs(delta) < 1e-8) 
        break; 
    }
    if (fabs(delta) >= 1e-8) {
            fprintf(stderr,"line %d: solver did not converge \n", line_number);
            exit(1);
    }
    
    


    return I = current_I; 
}


/*
* Purpose:      Check whether I is 0.0.  If it is, report an error ("I must
*               be positive"), and exit the program with an exit code of 1.
*
*               For more information, see section 4.2 of the Assignment PDF.
*
* Parameters:   line_number for any error messages.
*
* Returns:      Nothing.
*/
void check_I(int line_number) {
        if (I == 0.0) {
        fprintf(stderr,"line %d: I must not be zero \n", line_number);
        exit(1);
        }
    

}

double compute_pv(double fv, double i, double n, double pmt) {
    double x = pow(1 + i, -n);
    double pv = -pmt *(((1 - x)/ i)) - ( fv * x);
    return pv;
}

// Computes the equation for pmt

double compute_pmt(double n, double i, double pv, double fv) {
    double x = pow(1 + i, n);
    double pmt = i * ((pv * x  + fv) /( 1 - x));
    return pmt;
}

// Computes the equation for FV

double compute_fv(double pv, double i, double n, double pmt) {
    // ( 1 + I)**N
    double x = pow(1 + i, n);
    double fv = -pv * x - pmt * ((x - 1) / i);
    return fv;
}

/*
* Purpose:      Compute and print a variable's new value.
*
*               For more information, see these sections of the Assignment
*               PDF: 6.1, 6.2, and 6.3.
*
* Parameters:   name        -- of the variable to compute
*               line_number -- for any error messages
*
* Returns:      Nothing.
*/
void tvm_compute_variable(char *name, int line_number) {
    
    if (strcmp(name, "N") == 0 ) {
        check_I(line_number);
        //printf("%.6f\n",I);
        //printf("%.6f\n",PV);
        //printf("%.6f\n",PMT);
        //printf("%.6f\n",FV);
        printf("N = %.0f\n", newton_raphson_N(line_number));
        
    
    
       
    }else if (strcmp(name, "I") == 0) {
        //printf("%.6f\n",N);
        //printf("%.6f\n",PV);
        //printf("%.6f\n",PMT);
        //printf("%.6f\n",FV);
        printf("I = %.6f\n", newton_raphson_I(line_number));

    }else if (strcmp(name, "PV") == 0) {
        //printf("%.2f\n",N);
        //printf("%.2f\n",I);
        //printf("%.2f\n",PMT);
        //printf("%.2f\n",FV);
        printf("PV = %.2f\n", compute_pv(FV, I, N, PMT));
        
     
    }else if (strcmp(name, "PMT") == 0) {
 // printf("%.2f\n",N);
 //  printf("%.2f\n",I);
 // printf("%.2f\n",PV);
 //  printf("%.2f\n",FV);
        printf("PMT = %.2f\n", compute_pmt(N, I, PV, FV));
        
    
    }else if (strcmp(name, "FV") == 0) {
        //printf("%.2f\n",N);
        //printf("%.2f\n",I);
        //printf("%.2f\n",PMT);
        //printf("%.2f\n",PV);
        printf("FV = %.2f\n", compute_fv(PV, I, N, PMT));


    }else {
        fprintf(stderr, "line %d: invalid variable name \n", line_number);
        exit(1);
    }

    
    

    
}


/*
* Purpose:      Set a variable's new value.
*
* Parameters:   name and line_number for any error messages.
*               value is the variable's new value.
*
* Returns:      Nothing.
*/
void tvm_set_variable(char *name, double value, int line_number) {
//N = value;
//I = value;
//PV = value;
//PMT = value;
//FV = value; 
//double N, I, PV, PMT, FV;





    if (strcmp(name, "N") == 0 ) {
    
       if((int)value <= 0 || (int)value != (double)value) {
          fprintf(stderr, "line %d: N must be postive integer \n", line_number);
          exit(1);
       }
        N = value;
   // printf("N is set to %f \n", N);

    } else if (strcmp(name, "I") == 0 ) {
      if (value < 0 || (int)value < 0){
          fprintf(stderr,"line %d: I must be postive \n", line_number);
          exit(1);
      }
      I = value;
      return;
    //printf("I is set to %f \n", I);
    
    } else if (strcmp(name, "PV") == 0 ) {
        PV = value;
        return;
   // printf("PV is set to %f \n", PV);
    
    } else if (strcmp(name, "PMT") == 0 ) {
       PMT = value;
       return;
    //  printf("PMT is set to %f \n", PMT);
    } else if (strcmp(name, "FV") == 0) {
        FV = value;
        return;
 // printf("FV is set to %f \n", FV);
    
    } else {
        fprintf(stderr, "line %d: invalid variable name \n", line_number);
        exit(1);
    }
}


/*
* Purpose:      Clear all of the financial variables:  N, I, PV, PMT, and FV.
*
* Parameters:   None.
*
* Returns:      Nothing.
*/
void tvm_clear(void) {
N = 0;
I = 0;
PV = 0;
PMT = 0;
FV = 0;
}


/*
* Purpose:      Process one of these commands, or print an error and exit.
*
*                   "set VAR NUMBER"
*                   "compute VAR"
*                   "clear"
*
* Parameters:   command:        A string that represents the command.
*               line_number:    The line number of the command, for errors.
*
* Returns:      Nothing
*/
void tvm_process_command(char *command, int line_number) {

    char var_name[11]; // 10 characters + 1 null character
    double value = 0;
    
    // %10f - at most 10 characters
    // %lf -> double
    // & - address of operation
    if (sscanf(command, "set %10s %lf", var_name, &value) == 2) {
        // If the two things were found successfully
        // Print this ( == 2 means that they were found successfully)
        // use man scanf for this to check
        tvm_set_variable(var_name, value, line_number);
    } else if(sscanf(command, "compute %10s", var_name) == 1) {
        tvm_compute_variable(var_name, line_number);
    } else if (strcmp(command, "clear") == 0) {
        tvm_clear();
    } else if (strcmp(command, "") == 0) {

    } else {
        // %d - format specifier for an int
        fprintf(stderr, "line %d: invalid command \n", line_number);
        exit(1);
    }
}


/*
* Purpose:      Truncate string s at the first occurance of '\n'.
*               If s has no '\n', then do nothing.
*
*               The end of a string is denoted by a 0 byte, sometimes
*               called '\0'.  So overwriting any '\n' with '\0' will
*               truncate the string just before the '\n'.
*
* Parameter:    s is a string
*
* Returns:      Nothing
*/
void truncate_at_newline(char *s) {
    int j = 0;

    while (s[j] != '\0' && s[j] != '\n') ++j;

    s[j] = '\0';
}
/*
* Purpose:      Read commands from stdin, and process them.
* Parameters:   None
* Exit code:    1 on error, else 0
*/

int main(void) {
    char command[40];

    int line_number = 0;

    tvm_clear();

    while (1) {
        char *res = fgets(command, sizeof(command), stdin);

        if (res == NULL) break;

        ++line_number;
        truncate_at_newline(command);
        tvm_process_command(command, line_number);
    }

    if (ferror(stdin)) {
        fprintf(stderr, "tvm:  Error reading input\n");
        exit(1);
    }

    return 0;
}
