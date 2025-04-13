#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define atoa(x) #x
#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))
#define NUM_ROWS(a) ARRAYSIZE(a)
#define NUM_COLS(a) ARRAYSIZE(a[0])
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

typedef struct{
	char cid_locnum_vid[20];
	int test_target;
} record;

typedef struct custtrain{
	char cust_id[15];
	int cust_freq;
} Cust_Train;

typedef struct custtest{
	char cust_id[15];	
	int cust_freq;
} Cust_Test;

typedef struct locatest{
	char cust_id[15];
	int loc_num;
	int vend_id;
	int cust_freq;
} Loca_Test;

typedef struct cidlnumvid{
	char cid_lnum_vid[20];
	int cust_freq;
} Cid_Lnum__Vid;

typedef struct submatrix{
	char cid_lnum_vid[20];
	char target[5];
} Sub_Matrix;

struct filter {	
	int sno;
	int freq;
	char cust_id[15];
	int key;
	struct filter *next;
};

struct node {
   char *data1;
   char *data2;
   int key;
   struct node *next;
};

struct splitFieldType {
    char *field;
    int   maxLength;
};

typedef struct splitFieldType splitField;

struct stringFieldsType {
    char field1[9];
    char field2[3];
    char field3[5];
    char field4[3];
    char field5[6];
  } stringFields;
  
typedef struct splitFieldType splitField;

struct filter *first = NULL;
struct filter *current = NULL;
struct filter *new = NULL;
struct node *head = NULL;
struct node *current0 = NULL;

int tltestrow = 16720;
int tctestrow = 9768;	
int tctrainrow = 34674;
int cidlnovidrow = 135303;
int submissionrow = 1048574;

record test_data;
Cust_Train tctrain[34674];
Cust_Test tctest[9768];	
Loca_Test tltest[16720];
Cid_Lnum__Vid cidlnovid[135303];
Sub_Matrix submission[1048574];
//char **cidlnovid = NULL;
//char *cidlnovid_elems[5];

void createTrainCustomerCidFreqMatrix(void);
void createTestCustomerCidFreqMatrix(void);
void createTestCidLocnoTargetMatrix(void);
void createOrderCidLocnoVidMatrix(void);
void createSubmissionMatrix(void);
//char *substring(int i, int j, char *ch);
char *concatenate_string(char *char1, char *char2, char *char3);
void simulateModel(void);
//void splitString(char *str);
void append(record *recfield, FILE *ptr, char *cidlnvid, int tltarget);
//int stringToInt(char[]);
bool searchForElemment(char *elem1, char *elem2);
void insertFirst(int key, char *elem1, char *elem2);
//struct node* deleteFirst(void);
bool isEmpty(void);
int listLength(void);
//struct node* find(int key);
//struct node* delete(int key);
//void sort(void);
//char *getElemment(int key);
char *trimString(char * str);
struct filter *make_structure(void);
void fill_structure(struct filter *a, int c, int f, char *cid, int ky);
int getIndex(int n);
void emptyList(void);
void strSplitSoftError(int fieldNumber, int expected, int actual);
int strsplit(splitField *fields, int expected, const char *input, const char *fieldSeparator, void (*softError)(int fieldNumber,int expected,int actual));
int compare_string(char *first, char *second);
void show_structure(struct filter *a);
int filterLength(void);
//void free_array(char** in_array);

int main(void) {
	printf("Data proccessing is ongoing ...... \n");
	time_t start_seconds; 
   
     // Stores time seconds 
    time(&start_seconds); 
    char* start_time_string = ctime(&start_seconds);
    
	//createTrainCustomerCidFreqMatrix;	
	createTestCustomerCidFreqMatrix();
	createTestCidLocnoTargetMatrix();
	createSubmissionMatrix();		
	//createOrderCidLocnoVidMatrix();
	
	simulateModel();
	time_t stop_seconds; 
   
    // Stores time seconds 
    time(&stop_seconds); 
        
    char* stop_time_string = ctime(&stop_seconds);
    printf("                              ");
                
    printf("Starting time is %s", start_time_string);
    printf("Starting time is %s", stop_time_string);
	float seconds = difftime(stop_seconds, start_seconds);	
    printf("Time Elapsed is %f ", seconds);   
    
	return 0;
}

void createTrainCustomerCidFreqMatrix(void){
    FILE *fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/train_cid_frequency.csv", "r");

    if (!fp){
        printf("Can't open file\n");
        return;
    }

    //int rows = 34674;		
	char buf[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;
    
	while (fgets(buf, 1024, fp)){
		
        field_count = 0;
        row_count++;

        if (row_count == 1){
            continue;
        }
	   		 
        char *field = strtok(buf, ",");
        while (field != 0){
            //char *holdfield;   
            //strcpy(holdfield, field); 
                
            if (field_count == 0){
                //tctrain[i].cust_id = field;
                strcpy(tctrain[i].cust_id, field);
		        //sprintf(arr[i][0], "%s", holdfield);
            }
            if (field_count == 1){
                tctrain[i].cust_freq = atoi(field);
            }              
            
            //printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        //printf("TrainCustCidFreq: %d, %s, %d\n", i, tctrain[i].cust_id, tctrain[i].cust_freq);
	    i++;
        //if (row_count == rows){
        //    break;
        //}
        //printf("\n");
    } 

    printf("createTrainCustomerCidFreqMatrix (tctrain generated)\n");
    fclose(fp);
}

void createTestCustomerCidFreqMatrix(void){
    FILE *fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/tctest_cids_freqs.csv", "r");

    if (!fp){
        printf("Can't open file\n");
        return;
    }

    //int rows = 9768;		
	char buf[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;
        
	while (fgets(buf, 1024, fp)){
		
        field_count = 0;
        row_count++;

        if (row_count == 1){
            continue;
        }
	   		 
        char *field = strtok(buf, ",");
        while (field != 0){
            if (field_count == 0){
		        //tctest[i].cust_id = field;
		        strcpy(tctest[i].cust_id, field);
            }
            if (field_count == 1){
		        tctest[i].cust_freq = atoi(field);
            }              
            
            //printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        
        /*
        int seen = 0;
        for (int j = 0; j < tltestrow; j++){
			char *tltestcust_id = trimString(tltest[i].cust_id);
			char *tctestcust_id = trimString(tctest[j].cust_id);
			if (strcmp(tltestcust_id, tctestcust_id) == 0){
				seen = 1;
				//printf("tltestcust_id, tctestcust_id: %s, %s\n", tltestcust_id, tctestcust_id);
				//printf("(strcmp(tltestcust_id, tctestcust_id) == 0): %d\n", (strcmp(tltestcust_id, tctestcust_id) == 0));
				tctest[i].loc_num = tltest[j].loc_num;
				tctest[i].vend_id = tltest[j].vend_id;				
				break;
			}
        }
        if (seen == 0){
			tctest[i].loc_num = 0;
			tctest[i].vend_id = 0;
		}
		*/
		
		//printf("TestCusCidFreq: %d, %s, %d, %d, %d\n", i, tctest[i].cust_id, tctest[i].cust_freq, tctest[i].loc_num, tctest[i].vend_id);
	    i++;
        //if (row_count == rows){
        //    break;
        //}
        //printf("\n");
    } 

    printf("createTestCustomerCidFreqMatrix (tctest generated)\n");
    fclose(fp);
}

void createTestCidLocnoTargetMatrix(void){
    FILE *fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/tltest_cids_locnos_target.csv", "r");

    if (!fp){
        printf("Can't open file\n");
        return;
    }

    //int rows = 16720;	
	char buf[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;
    
	while (fgets(buf, 1024, fp)){
		
        field_count = 0;
        row_count++;

        if (row_count == 1){
            continue;
        }
	   		 
        char *field = strtok(buf, ",");
        while (field != 0){
            if (field_count == 0){
		        //tltest[i].cust_id = field;
		        strcpy(tltest[i].cust_id, field);
            }
            if (field_count == 1){
		        tltest[i].loc_num = atoi(field);
            } 
            if (field_count == 2){
		        tltest[i].vend_id = atoi(field);
            }              
            
            //printf("%s\n", field);
            field = strtok(NULL, ",");

            field_count++;
        }
        
        for (int j = 0; j < tctestrow; j++){
			char *tltestcust_id = trimString(tltest[i].cust_id);
			char *tctestcust_id = trimString(tctest[j].cust_id);
			if (strcmp(tltestcust_id, tctestcust_id) == 0){
				tltest[i].cust_freq = tctest[j].cust_freq;				
				break;
			}
        }
        
        //printf("TestCidLocnoTarget: %d, %s, %d, %d, %d\n", i, tltest[i].cust_id, tltest[i].loc_num, tltest[i].vend_id, tltest[i].cust_freq);
	    i++;
        //if (row_count == rows) {
        //    break;
        //}
        //printf("\n");
    } 

    printf("createTestCidLocnoTargetMatrix (tltest generated)\n");
    fclose(fp);     
}

void createOrderCidLocnoVidMatrix(void){
    FILE *fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/CID_LOCNUM_VENDOR.csv", "r");

    if (!fp){
        printf("Can't open file\n");
        return;
    }

    //int rows = 135302;
	char buf[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;
    
    //cidlnovid = calloc(rows, sizeof(char*));
	while (fgets(buf, 1024, fp)){
		
        field_count = 0;
        row_count++;

        if (row_count == 1){
            continue;
        }
	   		 
        char *field = strtok(buf, ",");
        while (field != 0){
            if (field_count == 0){
		        //cidlnovid[i].cid_lnum_vid = field;
		        strcpy(cidlnovid[i].cid_lnum_vid, field);
		        //printf("OrderCidLocnoVid: %d, %s\n", i, cidlnovid[i].cid_lnum_vid);
            }          
            
            field = strtok(NULL, ",");

            field_count++;
        }
        int seen = 0;
        for (int j = 0; j < tctrainrow; j++){
			const char *fieldSeparator = " ";
			splitField cidlnovid_elems[5] = {
				{stringFields.field1,  sizeof(stringFields.field1)},
				{stringFields.field2,  sizeof(stringFields.field2)},
				{stringFields.field3,  sizeof(stringFields.field3)},
				{stringFields.field4,  sizeof(stringFields.field4)},
				{stringFields.field5,  sizeof(stringFields.field5)}
			};

			int expected = sizeof(cidlnovid_elems)/sizeof(splitField);
						
			int ct = strsplit(cidlnovid_elems, expected, cidlnovid[i].cid_lnum_vid, fieldSeparator, strSplitSoftError);

			if (ct != expected){
				//printf("string split %d fields, expected %d\n", ct, expected);
			}
						
			char *tctraincust_id = trimString(tctrain[j].cust_id);
			char *cidlnovidelems = trimString(cidlnovid_elems[0].field);
			if (strcmp(tctraincust_id, cidlnovidelems) == 0){
				seen = 1;
				//printf("tltestcust_id, tctestcust_id: %s, %s\n", tltestcust_id, tctestcust_id);
				//printf("(strcmp(tltestcust_id, tctestcust_id) == 0): %d\n", (strcmp(tltestcust_id, tctestcust_id) == 0));
				cidlnovid[i].cust_freq = tctrain[j].cust_freq;	
				//printf("i, cid_lnum_vid, freq: %s, %s\n", i, cidlnovid[i].cid_lnum_vid, cidlnovid[i].cust_freq);
			}
        }
        if (seen == 0)
			cidlnovid[i].cust_freq = 0;	
			
        //printf("i, cid_lnum_vid, freq: %d, %s, %d\n", i, cidlnovid[i].cid_lnum_vid, cidlnovid[i].cust_freq);
        
	    i++;
        //if (row_count == rows){
        //    break;
        //}
        //printf("\n");
    } 
    
    fclose(fp);
    printf("createOrderCidLocnoVidMatrix (cidlnovid generated)\n");    
}

void createSubmissionMatrix(void){
    FILE *fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/SampleSubmission.csv", "r");    

    if (!fp){
        printf("Can't open file\n");
        return;
    }

    //int rows = 135302;
	char buf[1024];
    int row_count = 0;
    int field_count = 0;
    int i = 0;
    
    //cidlnovid = calloc(rows, sizeof(char*));
	while (fgets(buf, 1024, fp)){
		
        field_count = 0;
        row_count++;

        if (row_count == 1){
            continue;
        }
	   		 
        char *field = strtok(buf, ",");
        while (field != 0){
            if (field_count == 0){
		        //cidlnovid[i].cid_lnum_vid = field;
		        strcpy(submission[i].cid_lnum_vid, field);
		        //printf("OrderCidLocnoVid: %d, %s\n", i, cidlnovid[i].cid_lnum_vid);
            }          
            
            field = strtok(NULL, ",");

            field_count++;
        }
        int seen = 0;
        for (int j = 0; j < tltestrow; j++){
			const char *fieldSeparator = " ";
			splitField cidlnovid_elems[5] = {
				{stringFields.field1,  sizeof(stringFields.field1)},
				{stringFields.field2,  sizeof(stringFields.field2)},
				{stringFields.field3,  sizeof(stringFields.field3)},
				{stringFields.field4,  sizeof(stringFields.field4)},
				{stringFields.field5,  sizeof(stringFields.field5)}
			};

			int expected = sizeof(cidlnovid_elems)/sizeof(splitField);
						
			int ct = strsplit(cidlnovid_elems, expected, submission[i].cid_lnum_vid, fieldSeparator, strSplitSoftError);

			if (ct != expected){
				//printf("string split %d fields, expected %d\n", ct, expected);
			}
						
			char *tltestcust_id = trimString(tltest[j].cust_id);
			char *cidlnovidelems = trimString(cidlnovid_elems[0].field);
			if (strcmp(tltestcust_id, cidlnovidelems) == 0){
				seen = 1;
				//printf("tltestcust_id, tctestcust_id: %s, %s\n", tltestcust_id, tctestcust_id);
				//printf("(strcmp(tltestcust_id, tctestcust_id) == 0): %d\n", (strcmp(tltestcust_id, tctestcust_id) == 0));
				//sprintf(str_target, "%d", target);
				sprintf(submission[i].target, "%d", tltest[j].vend_id);	
				//printf("i, cid_lnum_vid, freq: %s, %s\n", i, cidlnovid[i].cid_lnum_vid, cidlnovid[i].cust_freq);
				break;
			}
        }
        if (seen == 0)
			sprintf(submission[i].target, "%d", 0);
			
        //printf("i, cid_lnum_vid, freq: %d, %s, %d\n", i, cidlnovid[i].cid_lnum_vid, cidlnovid[i].cust_freq);
        
	    i++;
        //if (row_count == rows){
        //    break;
        //}
        //printf("\n");		
    } 
    
    fclose(fp);
    printf("createSubmissionMatrix (cidlnovid generated)\n");    
}

/*
// Use this to free
void free_array(char** in_array){
    char **pos = in_array;

    while (pos[0] != NULL){
        free(pos[0]);
        pos++;
    }

    free(in_array);
}
*/

char *trimString(char * str){
    int index, i;
    /*
     * Trim leading white spaces
     */
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n'){
        index++;
    }
	
    /* Shift all trailing characters to its left */
    i = 0;
    while(str[i + index] != '\0'){
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL
	
    /*
     * Trim trailing white spaces
     */
    i = 0;
    index = -1;
    while (str[i] != '\0'){
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
            index = i;
        }
        i++;
    }
	
    /* Mark the next character to last non white space character as NULL */
    str[index + 1] = '\0';
    
    char *newstr = str; 
    return newstr;  
}

int compare_string(char *first, char *second){
   while (*first == *second){
      if (*first == '\0' || *second == '\0')
         break;
         
      first++;
      second++;
   }

   if (*first == '\0' && *second == '\0')
      return 0;
   else
      return -1;
}

char *concatenate_string(char *char1, char *char2, char *char3){
	char target[80];
	char *ptarget;
	snprintf(target, sizeof(target), "%s X %s X %s", char1, char2, char3);
	ptarget = target;
	return ptarget;
}

void append(record *recfield, FILE *ptr, char *cidlnvid, int tltarget){ 
	//recfield->cid_locnum_vid = cidlnvid;
	strcpy(recfield->cid_locnum_vid, cidlnvid);
	recfield->test_target = tltarget;                          
	fprintf(ptr, "%s %d", recfield->cid_locnum_vid, recfield->test_target); 	                          
}  

void simulateModel(void){	
	FILE *fp;
	//long  n;

	fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/cidxlnoxvid_v2target.csv", "a");
	fprintf(fp, "%s, %s\n", "cid_X_lnum_X_vid", "target");
	
	//record test_data = {"VV00SSDD X 0 X 001", "1111"};
	//printf("Simulation is ongoing ...... ");	        	
    	
    /* Convert to local time format. */
    
    /*
    int n = 0;
    for (int kk = 0; kk < tctrainrow; kk++){
		bool found = searchForElemment(tctrain[kk].cust_freq);
		if (found == false){
			insertFirst(n,tctrain[kk].cust_freq);
			n++;
		}
    }
    //sort();
    int listlen = listLength();       
    emptyList();
    
    for (int l = 0; l < listlen; l++){ 
		int freq = getElemment(l);
		int flag = 0;
		int ii = 0;
		for (int jj = 0; jj < tctrainrow; jj++){
			if (freq == tctrain[jj].cust_freq){
				if (flag == 0){
					first = make_structure();
					current = first;
					flag = 1;					
				} else {
					new = make_structure();
					current->next = new;
					current = new;
				}
				fill_structure(current, jj, freq, tctrain[jj].cust_id, ii);
				ii++;
			}
		}
		//int filterlen = filterLength();
		//printf("simulateModel => ii, filterlen: %d, %d\n", ii, filterlen);	
		//printf("Press any character to continue .......\n");
		//int cc = getchar();
		//printf("cc: %i\n", cc);
	*/	
	//int n = 0;	
	for (int i = 0; i < submissionrow; i++){	
		//sprintf(cid_X_lnum_X_vid, "%s", ptrcXlnXvid);
		//sprintf(str_target, "%d", target);
		printf("%s, %s\n", submission[i].cid_lnum_vid, submission[i].target);	
		fprintf(fp, "%s,%s\n", submission[i].cid_lnum_vid, submission[i].target);
		
		/*		
		for (int ll = 0; ll < cidlnovidrow; ll++){
			//printf("simulateModel => point 11\n");
			const char *fieldSeparator = " ";
			splitField cidlnovid_elems[5] = {
					{stringFields.field1,  sizeof(stringFields.field1)},
					{stringFields.field2,  sizeof(stringFields.field2)},
					{stringFields.field3,  sizeof(stringFields.field3)},
					{stringFields.field4,  sizeof(stringFields.field4)},
					{stringFields.field5,  sizeof(stringFields.field5)}
			};

			int expected = sizeof(cidlnovid_elems)/sizeof(splitField);

			//printf("expecting %d fields\n",expected);

			int ct = strsplit(cidlnovid_elems, expected, cidlnovid[ll].cid_lnum_vid, fieldSeparator, strSplitSoftError);

			if (ct != expected){
				//printf("string split %d fields, expected %d\n", ct, expected);
			}
			if ((tltest[i].cust_freq == cidlnovid[ll].cust_freq) && (tltest[i].loc_num == atoi(cidlnovid_elems[2].field))){					
				//for (int i = 0; i < expected; ++i){
					//	printf("field %d: %s\n",i+1,cidlnovid_elems[i].field);
				//}
				//printf("Press any character to continue .......\n");
				//int cc = getchar();
				//printf("cc: %i\n", cc);
					
				//char *tctraincust_id = trimString(tctrain[z].cust_id);
				//char *cidlnovidelems = trimString(cidlnovid_elems[0].field);
				//printf("tltest[i].cust_id, tctraincust_id, cidlnovidelems, tltest[i].cust_freq, tctrain[z].cust_freq: %s, %s, %s, %d, %d\n", tltest[i].cust_id, tctraincust_id, cidlnovidelems, tltest[i].cust_freq, tctrain[z].cust_freq);
				char cid_X_lnum_X_vid[20];		
				char *ptrcXlnXvid = concatenate_string(tltest[i].cust_id, cidlnovid_elems[2].field, cidlnovid_elems[4].field);
				int target = tltest[i].vend_id;
				char str_target[4];
				sprintf(cid_X_lnum_X_vid, "%s", ptrcXlnXvid);
				sprintf(str_target, "%d", target);
				printf("%s, %s\n", cid_X_lnum_X_vid, str_target);	
				fprintf(fp, "%s,%s\n", cid_X_lnum_X_vid, str_target);
				
			}													
		}
		*/				
	}
	    
    fclose(fp);
    
    //fp = fopen("C:/clang/projects/Akeed-Restaurant/Data/output.dat", "r");

	//while(ftell(fp) < n){
	//	fscanf(fp, "%s %s", test_data.cid_locnum_vid, test_data.test_target);
	//	fprintf(stdout,"%8s %8s\n", test_data.cid_locnum_vid, test_data.test_target);
	//}
	//fclose(fp);	
    
    //free_array(cidlnovid);     
}

int strsplit(splitField *fields, int expected, const char *input, const char *fieldSeparator, void (*softError)(int fieldNumber,int expected,int actual)){
    int i;
    int fieldSeparatorLen = strlen(fieldSeparator);
    const char *tNext, *tLast = input;
	//fprintf(stderr,"stringSplit => input: %s\n", input);  
    for (i = 0; i < expected && (tNext = strstr(tLast, fieldSeparator)) != NULL; ++i){
        int len = tNext - tLast;
        if (len >= fields[i].maxLength){
            softError(i, fields[i].maxLength - 1, len);
            len = fields[i].maxLength - 1;
        }
        fields[i].field[len] = 0;
        strncpy(fields[i].field, tLast, len);
        //fprintf(stderr,"stringSplit => i, fields[i].field: %d, %s\n", i, fields[i].field);  
        tLast = tNext + fieldSeparatorLen;
    }
    if (i < expected){
        if (strlen(tLast) > fields[i].maxLength){
            softError(i, fields[i].maxLength, strlen(tLast));
        } else {
            strcpy(fields[i].field, tLast);
            //fprintf(stderr,"stringSplit => i, fields[i].field: %d, %s\n", i, fields[i].field);            
        }
        return i + 1;
    } else {
        return i;
    }
}

void strSplitSoftError(int fieldNumber, int expected, int actual) {
    //fprintf(stderr,"strSplit: input field #%d is %d bytes, expected %d bytes\n", fieldNumber + 1, actual, expected);
}


int str_split(char *str, const char *delim, char ***array, int *length){
  int i=0;
  char *token;
  char **res = (char **) malloc(0 * sizeof(char *));

  /* get the first token */
   token = strtok(str, delim);
   while( token != NULL ) 
   {
        res = (char **) realloc(res, (i + 1) * sizeof(char *));
        res[i] = token;
        i++;
      token = strtok(NULL, delim);
   }
   *array = res;
   *length = i;
  return 1;
}

/*
void splitString(char *str){
	//char *newstring = (char*)malloc(5 * sizeof(char));
	char newstring[50];
	strcpy(newstring, str);
	char delim[] = " ";
	printf("splitString => point 0\n");
	printf("splitString => str: %s\n", newstring);
	char *ptr = strtok(newstring, delim);
	printf("splitString => ptr: %s\n", ptr);
	int i = 0;
	while(ptr != NULL){
		printf("splitString => point 1\n");
		//cidlnovid_elems[i] = ptr;
		strcpy(tltest[i].cust_id, ptr);
		printf("splitString => cidlnovid_elems[i]: %d %s\n", i, cidlnovid_elems[i]);
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
		i++;
	}				
	//return newstring;
}
*/

int stringToInt(char str[]){
	int i = 0, sum = 0;
    while(str[i]!='\0'){
		if (str[i] < 48 || str[i] > 57){  // ascii value of numbers are between 48 and 57.                
			//printf("Unable to convert it into integer.\n");
            return 0;
        } else {
			sum = sum*10 + (str[i] - 48);
			i++;
        }
    }
    return sum;
}

bool searchForElemment(char *elem1, char *elem2){
    struct node *temp;
	bool found = false; 
    // Return if list is empty 
    if(head == NULL){
        printf("List is empty.\n");
        return found;
    }
    
    temp = head;
    while(temp != NULL){
		char *param1 = trimString(elem1);
		char *param2 = trimString(elem2);
		char *temp_data1 = trimString(temp->data1);
		char *temp_data2 = trimString(temp->data2);	
			
		//if (elem == temp->data){
		if ((strcmp(param1, temp_data1) == 0) && (strcmp(param2, temp_data2) == 0)){
			found = true;
			//printf("searchForElemment => elem, Data: %d, %d\n", elem, temp->data); // Print data of current node
			break;
		}        
        temp = temp->next;                 // Move to next node
    }
    return found;
}

/*
char *getElemment(int key){
    //start from the first link
   struct node* current0 = head;

   //if list is empty
   if (head == NULL){
      return '\0';
   }

   //navigate through list
   while (current0->key != key){
	
      //if it is last node
      if(current0->next == NULL){
         return '\0';
      } else {
         //go to next link
         current0 = current0->next;
      }
   }      
	
   //if data found, return the current Link
   return current0->data;
}
*/

//insert link at the first location
void insertFirst(int key, char *data1, char *data2){
	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));
	
	link->key = key;
	link->data1 = data1;
	link->data2 = data2;
	//printf("insertFirst => key: %d, data: %d\n", link->key, link->data);	
	//point it to old first node
	link->next = head;
	
	//point first to new first node
	head = link;
}

/*
//delete first item
struct node* deleteFirst(void){

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}
*/

//is list empty
bool isEmpty(void){
   return head == NULL;
}

int listLength(void){
   int length = 0;
   struct node *current0;
	
   for (current0 = head; current0 != NULL; current0 = current0->next){
      length++;
   }
	
   return length;
}

/*
//find a link with given key
struct node* find(int key){

   //start from the first link
   struct node* current0 = head;

   //if list is empty
   if (head == NULL){
      return NULL;
   }

   //navigate through list
   while (current0->key != key){
	
      //if it is last node
      if(current0->next == NULL){
         return NULL;
      } else {
         //go to next link
         current0 = current0->next;
      }
   }      
	
   //if data found, return the current Link
   return current0;
}
*/

/*
//delete a link with given key
struct node* delete(int key){

   //start from the first link
   struct node* current0 = head;
   struct node* previous = NULL;
	
   //if list is empty
   if (head == NULL){
      return NULL;
   }

   //navigate through list
   while (current0->key != key){

      //if it is last node
      if (current0->next == NULL){
         return NULL;
      } else {
         //store reference to current link
         previous = current0;
         //move to next link
         current0 = current0->next;
      }
   }

   //found a match, update the link
   if (current0 == head){
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current0->next;
   }    
	
   return current0;
}

void sort(void){
   int i, j, k, tempKey;
   char *tempData;
   struct node *current0;
   struct node *next;
	
   int size = listLength();
   k = size;
	
   for (i = 0; i < size - 1; i++, k-- ){
      current0 = head;
      next = head->next;
		
      for (j = 1; j < k; j++ ){   

         if (current0->data > next->data ){
            tempData = current0->data;
            current0->data = next->data;
            next->data = tempData;

            tempKey = current0->key;
            current0->key = next->key;
            next->key = tempKey;
         }		 	
         current0 = current0->next;
         next = next->next;
      }
   }   
}
*/

struct filter *make_structure(void){
	struct filter *a;
	a = (struct filter *)malloc(sizeof(struct filter));
	if(a == NULL){
		puts("Some kind of malloc() error");
		return NULL;
	}
	return(a);
}

void fill_structure(struct filter *a, int c, int f, char *cid, int ky){
	a->sno = c;
	a->freq = f;	
	strcpy(a->cust_id, cid);
	a->key = ky;
	//printf("fill_structure => sno: %d, freq: %d, cust_id: %s, key: %d\n", a->sno, a->freq, a->cust_id, a->key);	
}

int getIndex(int n){
	current = first;
	int index = 0;
	while(current){		
		if (current->key == n){
			index = current->sno;
			//printf("getIndex => n: %d, sno: %d, freq: %d, cust_id: %s, key: %d\n", n, current->sno, current->freq, current->cust_id, current->key);	
			break;
		}		
		current=current->next;
	}
	return index;
}
 
void emptyList(void){
	if (first != NULL){
		first = NULL;
	}
}

int filterLength(void){
   int length = 0;
   struct filter *current;
	
   for (current = first; current != NULL; current = current->next){
      length++;
   }
	
   return length;
}
