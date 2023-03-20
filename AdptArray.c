#include <stdio.h>
#include <string.h>
#include "AdptArray.h"
#include <stdlib.h>

    // the struct of the adptArray, include the size of the array, pointer to the functions that the user
    // will create, and pointer to void *.
    typedef struct AdptArray_ {
        int size;
        COPY_FUNC cp;
        DEL_FUNC del;
        PRINT_FUNC pr;
        PElement* pt;
    }AdptArray;

    // create the adapt array
    PAdptArray CreateAdptArray (COPY_FUNC cp1, DEL_FUNC del1, PRINT_FUNC pr1) {
        PAdptArray p = (PAdptArray)calloc(1,sizeof(AdptArray));
        if (p == NULL) {
            return NULL;
        }
        p->size = 0;
        p->cp = cp1;
        p->del = del1;
        p->pr = pr1;
        p->pt = NULL;
        return p;
    }

    // return the element in the given index
    PElement GetAdptArrayAt (PAdptArray p, int inx) {
        if (p == NULL || (p->pt)[inx] == NULL) {
            return NULL;
        }
        // if the inx bigger than the size so the user dont put there element
        if (inx > p->size){
            return NULL;
        }
        else {
            // return copy of the element
            PElement tp = p->cp((p->pt)[inx]);
            return tp;
        }   
    }

    int GetAdptArraySize (PAdptArray p) {
        if (p == NULL) {
            return -1;
        }
        else return p->size;
    }

    Result SetAdptArrayAt(PAdptArray p, int inx, PElement pe) {
        if (p == NULL) {
            return FAIL;
        }
        if (inx >= p->size) {
            PElement newPe = (PElement*)calloc((inx + 1), sizeof(PElement));
            if (newPe == NULL) {
                return FAIL;
            }
            memcpy(newPe,p->pt,(p->size) * sizeof(PElement));
            free(p->pt);
            p->pt = newPe;
            p->size = inx + 1;
        }
        if (((p->pt)[inx]) != NULL) { 
        p->del((p->pt)[inx]);
        }
        (p->pt)[inx] = p->cp(pe);
        return SUCCESS;
    }

    void DeleteAdptArray(PAdptArray p) {
        if (p == NULL) {
            return;
        }
        for (int i = 0;i < p->size;i++) {
            if ((p->pt)[i]) {
                p->del((p->pt)[i]);
            }
        }
        free(p->pt);
        free(p);
    }

    void PrintDB(PAdptArray p) {
        if (p == NULL) {
            return;
        }
        for(int i = 0;i < p->size; i++){
            if ((p->pt)[i]){
                p->pr((p->pt)[i]);
            }
        }
    }

    // soureces for this prohect:
    // the answer for the moed A test in systems programminig A
    // the presentation for practice 11 in systems programminig A

