#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void login_page();
void quiz_page();
void view_quiz();
void quiz_details();
void main_page();


void flushstdin()
{
	int c;
	while((c=getchar())!='\n'&&c!=EOF);
}


void create_account()
{
	if(access("userid.csv",F_OK)==-1)
	{
		FILE *fp=fopen("userid.csv","w");
		fclose(fp);
	}
	FILE *user = fopen("userid.csv","r");
	
	char user_name_list[1000][100];
	int row=0,column=0,i,roll=0,count=0,exist=0;
	char buffer[1024];
	char userid[100] , password[20],password1[20] ;
	
	while(fgets(buffer,1024,user))
	{
		column=0;
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(user_name_list[count],value);
				count+=1;
			}
				
			value=strtok(NULL,",");
			column=column+1;
		}
		
		row++;
	}
	
	fclose(user);
	
	// open userid.csv in 'r' mode                        //completed
	// read all username in userid.csv                    //completed
	// close the userid.csv file                          //completed
	
	do
	{
		exist=0;
		system("cls");
		printf(" \n\n   ENTER THE USERNAME : ");
		fgets(userid,100,stdin);
		userid[strcspn(userid,"\n")]=0;
		for (i=0;i<count;i++)
			if (strcmp(userid,user_name_list[i])==0)
			{
				printf(" \n   Username already exists ... Enter another username\n\n");
				printf("Press any key to continue...");
				getch();
				exist=1;
			}

	}while(exist==1);
	// ask for username                                   //completed
	// check if username available in userid.csv          //completed
		// if available ask for another username          //completed
		
	do
	{
		exist=0;
		printf("\n   PASSWORD : ");
		fgets(password,20,stdin);
		password[strcspn(password,"\n")]=0;
		
		printf(" \n   CONFIRM PASSWORD : ");
		fgets(password1,20,stdin);
		password1[strcspn(password1,"\n")]=0;
		
		if (strcmp(password,password)!=0)
		{
			printf("\n\nPassword doesn't match ... Enter the password again");
		}
		
	}while(strcmp(password,password1)!=0);
	// ask for password 
	// confirm password

	user=fopen("userid.csv","a");
	
	fseek(user,0,SEEK_END);
	if (ftell(user)!=0)
		fprintf(user,"\n");
		
	fprintf(user,"%s,%s",userid,password);
	
	fclose(user);
	
	mkdir(userid);
	printf("\nAccount Created Successfully! \n\nPress any key to continue...");
	getch();
	
	// open the userid.csv in 'a' mode           //completed
	// save the username in userid.csv           //completed
	// close userid.csv                          //completed
	
	
	login_page();
	//call login_page()                          //completed
	
}


void login_page()
{
	// open userid.csv in 'r' mode                          //completed
	// read all username and password                       //completed
	
	if(access("userid.csv",F_OK)==-1)
	{
		FILE *fp=fopen("userid.csv","w");
		fclose(fp);
	}
	FILE *user = fopen("userid.csv","r");
	
	char c,user_name_list[1000][100],user_password[1000][20];
	int row=0,column=0,i,j=0,roll=0,count=0,exist=0,found=0;
	char buffer[1024];
	char userid[100] , password[20] ;
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(user_name_list[count],value);
				count+=1;
			}
			
			if (column==1)
			{
				strcpy(user_password[count-1],value);
			}
				
			value=strtok(NULL,",");
			column=column+1;
		}
		
		row++;
	}
	
	fclose(user);
	
	do{
		system("cls");
		printf(" \n\n   ENTER YOUR USERNAME : ");
		fgets(userid,100,stdin);
		userid[strcspn(userid,"\n")]=0;
		
		printf(" \n   ENTER YOUR PASSWORD : ");
		fgets(password,20,stdin);
		password[strcspn(password,"\n")]=0;
		
		j+=1;
		
		for (i=0;i<count;i++){
			if ((strcmp(userid,user_name_list[i])==0)&&(strcmp(password,user_password[i])==0)){
				char user_file[100];
				strcpy(user_file,userid);
				found=1;
				quiz_details(userid,user_file);
				return;
			}
		}
		
		if(found==0)
		{
			printf("\nEnter valid username and password!\n\nPress any key to continue ...");
			getch();
		}
	}while(j<3);
	
	if(i==count){
		printf(" \nDO YOU WANT TO CREATE A NEW ACCOUNT(Y) : ");
		scanf("%c",&c);
		flushstdin();
		if (c=='Y' || c=='y')
			create_account();
	}

	// completed and attached
	
	// get username and password from user
	// verify with existing
	// if verification successful call quiz_details()
	// else ask whether to create new account 
		// if yes -> call create_account()
	//completed
}

void quiz_details(char userid[100],char user_titles[100])
{	
	int b ;

	strcat(user_titles,"/quiz_titles.csv");
	
	
	if(access(user_titles,F_OK)==-1)
	{
		FILE *fp=fopen(user_titles,"w");
		fclose(fp);
	}
	FILE *user = fopen(user_titles,"r");
	
	char title[1000][100],code[1000][20],user_name[1000][50];
	int row=0,column=0,i,roll=0,count=0,exist=0,trail =0;
	char buffer[1024];
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (trail==0)
			{
				printf("\n   S.No\t\tUser Name\tQuiz Title\tQuiz Code");
				trail++;
			}
			if (column==0)
			{
				strcpy(user_name[count],value);
				count+=1;
				printf(" \n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n   %-20d\t%-20s",count,user_name[count-1]);
			}
			if (column==1)
			{
				strcpy(title[count-1],value);
				printf("\t%-20s\t",title[count-1]);
			}
			
			if (column==2)
			{
				strcpy(code[count-1],value);
				printf("%-20s\n",code[count-1]);
			}
				
			value=strtok(NULL,",");
			column=column+1;
		
		}
		
		row++;
	}
	
	fclose(user);

	printf("\n\n\nDO YOU WANT TO CREATE A NEW QUIZ(1) : ");
	scanf("%d", &b);
	flushstdin();

	if(b==1)
	{
		quiz_page(userid,user_titles);
	}
	
	else
		printf(" \n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Thank you  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");

	// open quiz_titles.csv in 'r' mode   //completed - completed
	// view available quizzes             //completed - completed
	// close quiz_titles.csv	          //completed - completed
	// ask whether to create new quiz     //completed - completed
		// if yes -> call quiz_page()     //completed - completed
}

void quiz_page(char userid[100],char user_titles[100])
{
	
	if(access(user_titles,F_OK)==-1)
	{
		FILE *fp=fopen(user_titles,"w");
		fclose(fp);
	}
	FILE *user = fopen(user_titles,"r");
	
	char title[1000][100],str_count[10],code[1000][20],user_name[1000][50],new_title[100],quiz_code[100];
	int row=0,column=0,i,roll=0,count=0,exist=0;
	char buffer[1024],question_file[100];
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(user_name[count],value);
				count+=1;
			}
			if (column==1)
				strcpy(title[count-1],value);
			
			if (column==2)
				strcpy(code[count-1],value);
				
			value=strtok(NULL,",");
			column=column+1;
		}
		
		row++;
	}
	fclose(user);
	
	do
	{
		system("cls");
		exist=0;
		printf("\n\n   Enter the quiz title : ");
		fgets(new_title,100,stdin);
		new_title[strcspn(new_title,"\n")]=0;
		
		for (i=0;i<count;i++)
		{
			if (strcmp(new_title,title[i])==0){
				exist=1;
				printf("\nQuiz Title already exists!\n\nEnter another title...");
				getch();
				break;
			}
		}
		
	}while(exist==1);
		
	// open quiz_titles.csv in 'r' mode        -------------- completed -----------
	// ask for title of quiz                   ---------------- completed -----------
	// check whether title is available in quiz_titles.csv         ---------------- completed -------------
		// if available ask for another title     --------------- completed ---------------
	// close quiz_titles.csv                   -------------- completed ------------------
	
	itoa(count+1,str_count,10);
	strcpy(quiz_code,userid);
	strcat(quiz_code,"_0");
	strcat(quiz_code,str_count);
	
	// generate code to access the quiz  ----- completed -------

	if(access("quiz_titles.csv",F_OK)==-1)
	{
		FILE *fp=fopen(user_titles,"w");
		fclose(fp);
	}
	FILE* quiz_title_file=fopen("quiz_titles.csv","a");
	
	user = fopen(user_titles,"a");
	// open quiz_titles.csv in 'a' mode    --- completed ------
	fseek(user,0,SEEK_END);
	if (ftell(user)!=0)
		fprintf(user,"\n");
		
	fprintf(user,"%s,%s,%s",userid,new_title,quiz_code);
	
	
	fseek(quiz_title_file,0,SEEK_END);
	
	if (ftell(quiz_title_file)!=0)
		fprintf(quiz_title_file,"\n");
	
	fprintf(quiz_title_file,"%s,%s,%s",userid,new_title,quiz_code);
	// add user name , title and code to quiz_titles.csv ----------- completed ------------------
	// close quiz_title.csv  ---------------------- completed ---------------
	fclose(user);
	fclose(quiz_title_file);
	
	strcpy(question_file,userid);
	strcat(question_file,"/");
	strcat(question_file,new_title);
	strcat(question_file,".csv");
	
	if(access(question_file,F_OK)==-1)
	{
		FILE *fp=fopen(question_file,"w");
		fclose(fp);
	}
	
	user=fopen(question_file,"a");
	
	int total,q_no=0;
	
	printf("\n   Enter total number of questions : ");
	scanf("%d",&total);
	flushstdin();
	
	int temp;
	char question[total][100],option1[total][50],option2[total][50],option3[total][50],option4[total][50],answer[total][50];
	
	for(i=0;i<total;i++)
	{
		system("cls");
		printf("\n Enter details of question %d:\n",i+1);
		
		printf("\tQuestion: ");
		fgets(question[i],100,stdin);
		question[i][strcspn(question[i],"\n")]=0;

		printf("\tOption 1: ");
		fgets(option1[i],50,stdin);
		option1[i][strcspn(option1[i],"\n")]=0;
	
		printf("\tOption 2: ");
		fgets(option2[i],50,stdin);
		option2[i][strcspn(option2[i],"\n")]=0;
	
		printf("\tOption 3: ");
		fgets(option3[i],50,stdin);
		option3[i][strcspn(option3[i],"\n")]=0;
	
		printf("\tOption 4: ");
		fgets(option4[i],50,stdin);
		option4[i][strcspn(option4[i],"\n")]=0;
		
		while(1)
		{
			printf(" Correct Answer (1/2/3/4): ");
			scanf("%d",&temp);
			flushstdin();
			switch(temp){
				case 1:
					strcpy(answer[i],option1[i]);
					break;
				case 2:
					strcpy(answer[i],option2[i]);
					break;
				case 3:
					strcpy(answer[i],option3[i]);
					break;
				case 4:
					strcpy(answer[i],option4[i]);
					break;
				
				default:
					printf("\nEnter the valid option\n");
					continue;
			}
			break;
		}
		
		fseek(user,0,SEEK_END);
		if (ftell(user)!=0)
			fprintf(user,"\n");
			
		fprintf(user,"%s,%s,%s,%s,%s,%s",question[i],option1[i],option2[i],option3[i],option4[i],answer[i]);
		
		q_no+=1;
	}
	
	printf("\n\nQuiz Created Successfully!\n\n   => QUIZ CODE = %s ",quiz_code);
	printf("\n\nPress any key to continue ...");
	getch();
	
	fclose(user);
	
	main_page();
	// create a csv file with name of title and open in 'a' mode  -------------- completed --------------
	// ask for the number of questions                 --------------------- completed -------------------
	// get all the questions and its correct option       ------------------ completed -------------------
	// store the questions and answer in the csv file created  ------------ completed --------
	// close the csv file      ------------------------ completed ---------------
	
	// call main_page()        ------------------ completed --------------------------
}


void create_quiz()
{
	int a ;
	menu: 
		system("cls");
		printf(" \n\n   NEW USER (1)  or  EXISTING USER (2) : ");
		scanf("%d", &a);
		flushstdin();
	
		if (a==1)
			create_account();
		
		else if (a==2)
			login_page();
			
		else 
			goto menu;
		

	// Ask for existing user or new user     //completed - completed
	// if new user call create_account()     //completed - completed
	// if existing user call login_page()    //completed - completed
	
}

void code_verify()
{
	// open quiz_titles.csv in 'r' mode                 // completed
	
	if(access("quiz_titles.csv",F_OK)==-1)
	{
		FILE *fp=fopen("quiz_titles.csv","w");
		fclose(fp);
	}
	FILE *user = fopen("quiz_titles.csv","r");
	
	char title[1000][100],code[1000][20],e_code[20],user_name[1000][100];
	int row=0,column=0,i,roll=0,count=0,exist=0;
	char buffer[1024];
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(user_name[count],value);
				count+=1;
			}
			if (column==1)
			{
				strcpy(title[count-1],value);
			}
			
			if (column==2)
			{
				strcpy(code[count-1],value);
			}
				
			value=strtok(NULL,",");
			column=column+1;
		
		}
		
		row++;
	}
	
	fclose(user);
	
	while (1)
	{
		printf("\n\n   Enter the code : ");
		fgets(e_code,20,stdin);
		e_code[strcspn(e_code,"\n")]=0;
		// ask for code from user               // completed
		
		for(i=0;i<count;i++)
		{
			if (strcmp(e_code,code[i])==0)
			{
				char slash[5]="/";
				strcat(slash,title[i]);
				strcat(slash,".csv");
				strcat(user_name[i],slash);
				
				view_quiz(user_name[i]);
				return;
			}
		}
		
		if(i==count)
		{
			printf("\n   Enter valid code");
			printf("\n\nPress any key to continue ...");
			getch();
			system("cls");
			continue;
		}
		else
		{
			break;
		}
	}
	
	
	//   ------------------------- completed --------------------------------------
	// compare the entered code with codes available in 'quiz_titles.csv'
		// if available title is retrieved and stored in a variable
		// if not user is asked to enter valid code
	// close quiz_titles.csv
	
	// call view_quiz(title)
	// ----------------------------- completed ----------------------------
	
}

void view_quiz_details()
{
	system("cls");
	
	if(access("quiz_titles.csv",F_OK)==-1)
	{
		FILE *fp=fopen("quiz_titles.csv","w");
		fclose(fp);
	}
	FILE *user = fopen("quiz_titles.csv","r");
	
	char title[1000][100],code[1000][20],e_code[20],user_name[1000][100];
	int row=0,column=0,i,roll=0,count=0,exist=0,j,trail1=0,count2=0,user_count=0,k;
	char buffer[1024],temp[100],temp1[1000][100],create_new,user_name_[1000][100];
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(user_name[count],value);
				count+=1;
			}
			if (column==1)
			{
				strcpy(title[count-1],value);
			}
			
			if (column==2)
			{
				strcpy(code[count-1],value);
			}
				
			value=strtok(NULL,",");
			column=column+1;
		}
		
		row++;
	}
	
	fclose(user);
	
	for(i=0;i<row;i++)
		strcpy(user_name_[i],user_name[i]);
	
	for(i=0;i<row;i++)
	{
		for(j=i+1;j<row;j++)
		{
			if (strcmp(user_name_[i],user_name_[j])>0)
			{
				strcpy(temp,user_name_[i]);
				strcpy(user_name_[i],user_name_[j]);
				strcpy(user_name_[j],temp);
			}
		}
	}

	
	for(i=0;i<row-1;i++)
		if (strcmp(user_name_[i],user_name_[i+1])!=0)
			strcpy(temp1[j++],user_name_[i]);
			
	strcpy(temp1[j++],user_name_[row-1]);
	
	for (i=0;i<j;i++)
		strcpy(user_name_[i],temp1[i]);
			

	for (i=0;i<1000;i++)
		if (user_name_[i][0]!='\0')
			user_count+=1;
		
	char user_titles1[1000][100];
	
	for (i=0;i<user_count;i++)
	{
		strcpy(user_titles1[i],user_name[i]);
	
		strcat(user_titles1[i],"/quiz_titles.csv");
		
		
		if(access(user_titles1[i],F_OK)==-1)
		{
			FILE *fp=fopen(user_titles1[i],"w");
			fclose(fp);
		}
		FILE *user1 = fopen(user_titles1[i],"r");
		
		char title1[1000][100],code1[1000][20],user_name1[1000][50];
		int row1=0,column1=0,i1,roll1=0,count1=0,exist1=0;
		char buffer1[1024],heading[4][20]={"S.No","User Name","Quiz Titles","Quiz Code"};
		while(fgets(buffer1,1024,user1))
		{
			column1=0;
				
			
			char* value1=strtok(buffer1, ",");
			while (value1)
			{
				value1[strcspn(value1,"\n")]=0;
				if (trail1==0)
				{
					printf("  ");
					for (j=0;j<4;j++)
						printf("%-20s\t",heading[j]);
					trail1++;
				}
				if (column1==0)
				{
					strcpy(user_name1[count1],value1);
					count1+=1;
					count2+=1;
					printf(" \n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");
					printf("\n   %-20d\t%-20s",count2,user_name1[count1-1]);
				}
				if (column1==1)
				{
					strcpy(title1[count1-1],value1);
					printf("\t%-20s\t",title1[count1-1]);
				}
				
				if (column1==2)
				{
					strcpy(code1[count1-1],value1);
					printf("%-20s\n",code1[count1-1]);
				}
					
				value1=strtok(NULL,",");
				column1=column1+1;
			
			}
			
			row1++;
		}
		
		fclose(user1);
	
	}
	
	if(user_count!=0)
		code_verify();
		
	else
	{
		printf("\n\n   No Quizzes Available\n\n");
		
		printf("Do you want to Create New Quiz(Y/N): ");
		scanf("%c",&create_new);
		flushstdin();
		
		if (create_new=='Y' || create_new=='y')
			create_quiz();
			
	}
	
}

void view_quiz(char file_path[100])
{	

	if(access(file_path,F_OK)==-1)
	{
		FILE *fp=fopen(file_path,"w");
		fclose(fp);
	}
	FILE *user=fopen(file_path,"r");
	// open title.csv in 'r' mode
	
	
	char question[1000][100],option1[1000][100],option2[1000][100],option3[1000][100],option4[1000][100],answer[1000][100];
	int row=0,column=0,count=0,i,temp,marks=0;
	char buffer[1024],entered_answer[1000][100];
	while(fgets(buffer,1024,user))
	{
		column=0;
			
		
		char* value=strtok(buffer, ",");
		
		while (value)
		{
			value[strcspn(value,"\n")]=0;
			if (column==0)
			{
				strcpy(question[count],value);
				count+=1;
			}
			
			if (column==1)
				strcpy(option1[count-1],value);
			
			if (column==2)
				strcpy(option2[count-1],value);
				
			if (column==3)
				strcpy(option3[count-1],value);
			
			if (column==4)
				strcpy(option4[count-1],value);
				
			if (column==5)
				strcpy(answer[count-1],value);
				
			value=strtok(NULL,",");
			column=column+1;
		}
		
		row++;
	}
	fclose(user);

	// read all the questions and options from the csv file and store the data ---------- completed ----------------
	// close title.csv              ----------------------- completed ---------------------------
	
	system("cls");
	
	for (i=0;i<count;i++)
	{
		printf("\n\nQuestion number %d :\n\n",i+1);
		printf("%s\n\n",question[i]);
		printf("Option 1: %s\nOption 2: %s\nOption 3: %s\nOption 4: %s\n\n",option1[i],option2[i],option3[i],option4[i]);
		printf("Enter your answer (1/2/3/4): ");
		scanf("%d",&temp);
		flushstdin();
		
		switch(temp){
			case 1:
				strcpy(entered_answer[i],option1[i]);
				break;
			case 2:
				strcpy(entered_answer[i],option2[i]);
				break;
			case 3:
				strcpy(entered_answer[i],option3[i]);
				break;
			case 4:
				strcpy(entered_answer[i],option4[i]);
				break;
				
			default:
				printf("Enter the valid option\n");
				continue;
		}
	}
	// print each question and ask the user to enter the option     ---------- completed --------------
	
	for (i=0;i<count;i++)
	{
		if (strcmp(entered_answer[i],answer[i])==0){
			marks++;
		}
	}
	
	printf("\nAll the answers are recorded\n\nPress any key to continue...");
	getch();
	
	system("cls");
	
	printf("\n\n=>   YOU HAVE SCORED %d OUT OF %d\n",marks,count);
	
	printf("\nCorrect answers:\n");
	
	for (i=0;i<count;i++){
		printf("\nQuestion : %s\nAnswer : %s\n",question[i],answer[i]);
	}
	printf("\n\nPress any key to continue ...");
	getch();
	
	// each answer entered is compared with correct answers and the scores are calculated  ------- completed --------
	// after completing all the questions user is asked to enter a key to continue ---------- completed ------------
	
	// display the total score and all the answers along with questions ------------ completed -------------
	
	
	main_page(); 
	// after completion of all process call main_page() ------------- completed -----------------
	
}


void main_page()
{
	int choice;
	system("cls");
	printf(" \n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \n\n   1. Create Quiz \n   2. View Available Quizzes \n\n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");
	do
	{
		printf("\n\n Enter your choice: ");
		scanf("%d",&choice);
		flushstdin();
		
	}while(choice<1||choice>2);
	
	switch(choice)
	{
		case 1:
			create_quiz();
			break;
			
		case 2:
			view_quiz_details();
			break;
	}
	
}


int main()
{

	main_page();
	
	return 0;
}
