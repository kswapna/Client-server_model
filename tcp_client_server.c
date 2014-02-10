#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include<string.h>
#include<unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <openssl/md5.h>
FILE *ok;
struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char   datestring[256];
void getfiles(char a[100]);
int Directory(char pzPath[100] );
char portnum[100];
char ser_portnum[100];
char ipaddress[100];
void ClientProcess();
void ServerProcess();
char files[1000][1000];
int filep=0;
char reg[1000][1000];
int rnum=0;

char md5string[MD5_DIGEST_LENGTH];
void md5(char *s)
{
	unsigned char c[MD5_DIGEST_LENGTH];
	char *filename=s;
	int i;
	FILE *inFile = fopen (filename, "rb");
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];
	if (inFile == NULL) {
		printf ("%s can't be opened.\n", filename);
	}   
	MD5_Init (&mdContext);
	while ((bytes = fread (data, 1, 1024, inFile)) != 0)
		MD5_Update (&mdContext, data, bytes);
	MD5_Final (c,&mdContext);
	for(i = 0; i < MD5_DIGEST_LENGTH; ++i)
		sprintf(&md5string[i*2], "%02x", (unsigned int)c[i]);
	fclose (inFile);
}
int Directory(  char pzPath[100] )
{
	if ( pzPath == NULL) return 0;
	DIR *pDir;
	int  bExists = 0;
	pDir = opendir (pzPath);
	if (pDir != NULL)
	{
		bExists = 1;    
		(void) closedir (pDir);
	}

	return bExists;
}
void getf(char *a){

	DIR *dp;
	struct dirent *ep;  
	struct stat statbuf;	
	dp = opendir (a);
	char c[100];

	if (dp != NULL)
	{
		while (ep = readdir (dp)){
			strcpy(c,a);
			char b[100];
			strcpy(b,ep->d_name);
			strcat(c,b);
		/*	if(Directory(c)==1){
				printf("**********%s\n",b);
				if(strcmp(".",b)!=0 && strcmp("..",b)!=0){ getf(c);}

			}*/
			if(Directory(c)==0){
				strcpy(files[filep],ep->d_name);
				printf("storing %s filep %d\n",ep->d_name,filep);
					filep++;
				char t[ 100 ] = "";
				struct stat bs;
				if (stat(c, &bs)==-1){
					filep++;
					continue;
				}
				if (!stat(c, &bs)) {
					char size[1000];
					sprintf(size,"%9jd",(intmax_t)bs.st_size);
					strcpy(files[filep],size);
					filep++;
					printf("eeee %s\n",size);
				}
				else {
					printf("Cannot display the time.\n");
				}
			}

		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
	return;
}


int month(char a[]){
	if(strcmp(a,"Jan")){
		return 1;
	}
	if(strcmp(a,"Feb")){
		return 2;
	}
	if(strcmp(a,"Mar")){
		return 3;
	}
	if(strcmp(a,"Apr")){
		return 4;
	}
	if(strcmp(a,"May")){
		return 5;
	}
	if(strcmp(a,"Jun")){
		return 6;
	}
	if(strcmp(a,"Jul")){
		return 7;
	}if(strcmp(a,"Aug")){
		return 8;
	}if(strcmp(a,"Sep")){
		return 9;
	}if(strcmp(a,"Oct")){
		return 10;
	}if(strcmp(a,"Nov")){
		return 11;
	}if(strcmp(a,"Dec")){
		return 12;
	}
}
void timestamp(char a[100],char *arg[100])
{
	DIR *dp;
	struct dirent *ep;  
	struct stat statbuf;	
	dp = opendir (a);
	char c[100];
	printf("enenenenenn %d %d %d %d %d %d %d %d %d %d\n",atoi(arg[3]),atoi(arg[4]),atoi(arg[5]),atoi(arg[6]),atoi(arg[7]),atoi(arg[8]),atoi(arg[9]),atoi(arg[10]),atoi(arg[11]),atoi(arg[12]));
	if (dp != NULL)
	{
		while (ep = readdir (dp)){
			strcpy(c,a);
			char b[100];
			strcpy(b,ep->d_name);
			strcat(c,b);
			if(Directory(c)==1){
				/*printf("**********%s\n",b);
				  if(strcmp(".",b)!=0 && strcmp("..",b)!=0){ getfiles(c);}*/
				continue;

			}
			if(Directory(c)==0){
				printf("file -%s       ",ep->d_name);
				char t[ 100 ] = "";
				struct stat bs;
				if (stat(c, &bs)==-1){
					continue;
				}
				if (!stat(c, &bs)) {
					tm = localtime(&bs.st_mtime);
					strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					printf(" %s %s\n", datestring, ep->d_name);
					char *result=NULL;
					char *da[10];
					int k=0;
					printf("%s\n",datestring);
					result = strtok(datestring, ":  \n" );
					printf("%s\n",result);
					while(result !=NULL ) {
						da[k]=result;
						printf("%s\n",result);
						printf("k=%d\n",k);
						result = strtok( NULL, ":  \n" );
						k++;
					}
					printf("k=%d\n",k);
					struct tm start;
					struct tm end;
					struct tm t;


					/*time_t rawtime,rawtime2;
					  struct tm * timeinfo;
					  struct tm * timeinfo2;
					  int year=2010, month=9 ,day=23;
					  double dif;
					  time ( &rawtime );
					  timeinfo = localtime ( &rawtime );
					  timeinfo->tm_year = year - 1900;
					  timeinfo->tm_mon = month - 1;
					  timeinfo->tm_mday = day;
					  timeinfo->tm_min =30;
					  mktime ( timeinfo );*/

					double sec1,sec2;
					t.tm_hour = atoi(da[3]); t.tm_min = atoi(da[4]); t.tm_sec = atoi(da[5]);
					t.tm_mon = month(da[1]);  start.tm_mday = atoi(da[2]); t.tm_year = atoi(da[6]);

					start.tm_hour = atoi(arg[5]); start.tm_min = atoi(arg[6]); start.tm_sec = atoi(arg[7]);
					start.tm_mon = atoi(arg[4]);  start.tm_mday = atoi(arg[3]); start.tm_year = atoi(arg[2]);

					end.tm_hour = atoi(arg[11]); end.tm_min = atoi(arg[12]); end.tm_sec = atoi(arg[13]);
					end.tm_mon = atoi(arg[10]);  end.tm_mday = atoi(arg[9]);end.tm_year = atoi(arg[8]);
					time_t t1 = mktime(&start);
					time_t t2 = mktime(&end);
					time_t ff = mktime(&t);
					printf("heehhehehe\n");
					sec1 = difftime(t1,ff);
					sec2 = difftime(t2,ff);
					printf("sec1=%lf  sec2=%lf\n",sec1,sec2); 
					if(sec1<=0 && sec2>=0){
						fputs(ep->d_name,ok);
						fputs("\n",ok);
						printf("yes***********************************************************\n");
					}
					/*if(t1 <= ff && ff <=t2){
						fputs(ep->d_name,ok);
						fputs("\n",ok);
					  printf("sahi hai Yes\n");
					  }*/
				}
				else {
					printf("Cannot display the time.\n");
				}
			}

		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
	return;

}



void getregex(char *a){
	FILE *ff;
	int fd;
	int status;
	char path[100];
	char command[100];
	strcpy(command,"ls");
	strcat(command," ");
	strcat(command,a);
	ff = popen(command, "r");
	if (ff == NULL)
	rnum=0;
	while (fgets(path, 100, ff) != NULL)
	{
		strcpy(reg[rnum],path);
		printf("%s",reg[rnum]);
		char *result=NULL;
		result=strtok(path,"\n");
		fputs(result,ok);
		fputs("   ",ok);
		FILE *fs = fopen(result, "r");
		fseek(fs, 0L, SEEK_END);
		long sz = ftell(fs);
		char len[1024];
		sprintf(len,"%ld",sz);
		fputs(len,ok);
		printf("%s\n",len);
		fputs("\n",ok);
		fclose(fs);
		rnum++;
	}
	pclose(ff);
}
	void getmd5(char a[100])
	{
		DIR *dp;
		struct dirent *ep;  
		struct stat statbuf;	
		dp = opendir (a);
		char c[100];

		if (dp != NULL)
		{
			while (ep = readdir (dp)){
				strcpy(c,a);
				char b[100];
				strcpy(b,ep->d_name);
				strcat(c,b);
				if(Directory(c)==1){
					if(strcmp(".",b)!=0 && strcmp("..",b)!=0){ getmd5(c);}

			}
			if(Directory(c)==0){
				fputs(ep->d_name,ok);
				fputs("  ",ok);
				char t[ 100 ] = "";
				struct stat bs;
				if (stat(c, &bs)==-1){
					continue;
				}
				if (!stat(c, &bs)) {
					tm = localtime(&bs.st_mtime);
					strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					fputs(datestring,ok);
					fputs("  ",ok);
				}
				else {
					fputs("cannot display the time",ok);
				}
				char md5string[MD5_DIGEST_LENGTH];
				unsigned char d[MD5_DIGEST_LENGTH];
				int i;
				FILE *inFile = fopen (c, "rb");
				MD5_CTX mdContext;
				int bytes;
				unsigned char data[1024];
				if (inFile == NULL) {
					printf ("%s can't be opened.\n", c);
				}   
				MD5_Init (&mdContext);
				while ((bytes = fread (data, 1, 1024, inFile)) != 0)
					MD5_Update (&mdContext, data, bytes);
				MD5_Final (d,&mdContext);
				for(i = 0; i < MD5_DIGEST_LENGTH; ++i)
					sprintf(&md5string[i*2], "%02x", (unsigned int)d[i]);
				fclose (inFile);
				fputs(md5string,ok);
				fputs(" \n",ok);
			}

		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
	return;
}
void getfiles(char a[100])
{
	DIR *dp;
	struct dirent *ep;  
	struct stat statbuf;	
	dp = opendir (a);
	char c[100];

	if (dp != NULL)
	{
		while (ep = readdir (dp)){
			strcpy(c,a);
			char b[100];
			strcpy(b,ep->d_name);
			strcat(c,b);
			if(Directory(c)==1){
				printf("**********%s\n",b);
				if(strcmp(".",b)!=0 && strcmp("..",b)!=0){ getfiles(c);}

			}
			if(Directory(c)==0){
				fputs(ep->d_name,ok);
				fputs("     ",ok);
				char t[ 100 ] = "";
				struct stat bs;
				if (stat(c, &bs)==-1){
					continue;
				}
				if (!stat(c, &bs)) {
					char size[1000];
					sprintf(size,"%9jd",(intmax_t)bs.st_size);
					fputs(size,ok);
					fputs("    ",ok);
					tm = localtime(&bs.st_mtime);
					strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					fputs(datestring,ok);
					fputs("    ",ok);
					fputs("\n",ok);
				}
				else {
					printf("Cannot display the time.\n");
				}
			}

		}
		(void) closedir (dp);
	}
	else
		perror ("Couldn't open the directory");
	return;
}
int main(int argc ,char *argv[])
{
	strcpy(portnum,argv[2]);
	strcpy(ipaddress,argv[1]);
	strcpy(ser_portnum,argv[3]);
	pid_t  pid;
	pid = fork();
	if (pid == 0)  
		ClientProcess();
	else 
		ServerProcess();
	return 0;
}
void ServerProcess(){
	filep=0;
	char *result=NULL;
	char *arg=NULL;
	int fd=0;
	int fu=0;
	int ll=0;
	int sl=0;
	int ver=0;
	int chk=0;
	int regex=0;
	int sock, connected, bytes_recieved , true = 1;  
	char send_data [1024] , recv_data[1024];       

	struct sockaddr_in server_addr,client_addr;    
	int sin_size;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	server_addr.sin_family = AF_INET;       
	int s_port=atoi(ser_portnum);
	server_addr.sin_port = htons(s_port);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr.sin_zero),8); 

	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1){
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock, 5) == -1) {
		perror("Listen");
		exit(1);
	}

	printf("\nTCPServer Waiting for client on port 5000\n");
	fflush(stdout);


	while(1)
	{ 
		//printf("oooo i m connected now\n");

		sin_size = sizeof(struct sockaddr_in);

		connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
		printf("Got a connection \n");

		printf("\n I got a connection from (%s , %d)",
				inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		while (1)
		{
			fd=0;

			char *args[100];
			fu=0;
			result=NULL;
			arg=NULL;
			filep=0;
			ll=0;
			sl=0;
			regex=0;
			int k=0;
			ver=0;
			chk=0;
			bytes_recieved = recv(connected,recv_data,1024,0);
			recv_data[bytes_recieved] = '\0';
			printf("\n%s\n",recv_data);
			if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
			{
				printf("Connection is broken\n");
				close(connected);
				break;
			}
			else {

				result = strtok(recv_data, " \n" );
				if(strcmp(result,"FileDownload")==0){
					fd=1;
				}
				if(strcmp(result,"FileUpload")==0){
					fu=1;
				}
				while(result !=NULL ) {
					args[k]=result;
					result = strtok( NULL, " \n" );
					k++;
				}
				if(strcmp(args[0],"FileDownload")==0){
					arg=args[1];
					fd=1;
				}
				if(strcmp(args[0],"FileUpload")==0){
					arg=args[1];
					fu=1;
				}
				if(strcmp(args[0],"IndexGet")==0){
					if(strcmp(args[1],"LongListing")==0){
						ll=1;
					}
					if(strcmp(args[1],"ShortListing")==0){
						sl=1;
					}
					if(strcmp(args[1],"RegEx")==0){
						regex=1;
					}
				}
				if(strcmp(args[0],"FileHash")==0){
					if(strcmp(args[1],"Verify")==0){
						ver=1;
					}
					if(strcmp(args[1],"CheckAll")==0){
						chk=1;
					}
				}




				if(regex==1){
	char sdbuf[1024]; // Send buffer
					ok=fopen(".regex","w");
					getregex(args[2]);
//					printf("retured from getregex\n\n");
					fclose(ok);
					FILE *fs = fopen(".regex", "r");
					fseek(fs, 0L, SEEK_END);
					long sz = ftell(fs);
					char len[1024];
					sprintf(len,"%ld",sz);
					write(connected,len,1024);
					fclose(fs);
					printf("%s\n",len);
					fs = fopen(".regex", "r");
					if(fs == NULL)
					{
						fprintf(stderr, "ERROR: File  not found on server. (errno = %d)\n", errno);
						exit(1);
					}
					bzero(sdbuf, 1024); 
					int fs_block_sz; 
					while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
					{
						if(write(connected, sdbuf, fs_block_sz) < 0)
						{
							fprintf(stderr, "ERROR: Failed to send file  (errno = %d)\n",  errno);
							exit(1);
						}
						sdbuf[fs_block_sz]='\0';
						bzero(sdbuf, 1024);
					}
					printf("Ok sent to client!\n");
					fclose(fs);
				}
				if(ver==1){
					char sdbuf[1024]; // Send buffer
					bzero(sdbuf, 1024); 
					FILE *fs=fopen(args[2],"r");
					if(fs==NULL){
						strcpy(sdbuf,"Sorry File not Found");
					write(connected,sdbuf,strlen(sdbuf));
					continue;
					}
					strcpy(sdbuf,"File Found!!!!!!!!!!");
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 
					md5(args[2]);
					strcpy(sdbuf,md5string);
				//	printf("%s\n",sdbuf);
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 
					struct stat bs;
					stat(args[2], &bs);
					tm = localtime(&bs.st_mtime);
					strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					bzero(sdbuf, 1024); 
					strcpy(sdbuf,datestring);
				//	printf("%s\n",sdbuf);
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 

				}
				if(chk==1){
					char sdbuf[1024]; // Send buffer
					ok=fopen(".md5.txt","w");
					getmd5("./");
					fclose(ok);
					FILE *fs = fopen(".md5.txt", "r");
					fseek(fs, 0L, SEEK_END);
					long sz = ftell(fs);
					char len[1024];
					sprintf(len,"%ld",sz);
					write(connected,len,1024 );
					fclose(fs);
					printf("%s\n",len);
					fs = fopen(".md5.txt", "r");
					if(fs == NULL)
					{
						fprintf(stderr, "ERROR: File  not found on server. (errno = %d)\n", errno);
						exit(1);
					}
					bzero(sdbuf, 1024); 
					int fs_block_sz; 
					while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
					{
						if(write(connected, sdbuf, fs_block_sz) < 0)
						{
							fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", arg, errno);
							exit(1);
						}
						sdbuf[fs_block_sz]='\0';
						bzero(sdbuf, 1024);
					}
					printf("Ok sent to client!\n");
					fclose(fs);
				}
				if(fd==1){


			//		printf("\n file to be downloaded = %s " , arg);
					char sdbuf[1024]; // Send buffer



					//size
					FILE *fs = fopen(arg, "r");
//checking whether file exists or not!!!!!!!!!!!!!!!

					if(fs==NULL){
					bzero(sdbuf, 1024); 
					strcpy(sdbuf,"Sorry File not Found");
					fclose(fs);
					write(connected,sdbuf,strlen(sdbuf));
					continue;
					}
					bzero(sdbuf, 1024); 
					strcpy(sdbuf,"File Found!!!!!!!!!!");
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 
					printf("[Server] Sending %s to the Client...", arg);
					fseek(fs, 0L, SEEK_END);
					long sz = ftell(fs);
					char len[1024];
					sprintf(len,"%ld",sz);
					write(connected,len,1024);
					fclose(fs);



					printf("%s\n",len);
					//md5
					md5(arg);
					bzero(sdbuf, 1024); 
					strcpy(sdbuf,md5string);
					printf("%s\n",sdbuf);
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 


					//timestamp 
						struct stat bs;
						stat(arg, &bs);
						tm = localtime(&bs.st_mtime);
						strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
					bzero(sdbuf, 1024); 
					strcpy(sdbuf,datestring);
					printf("%s\n",sdbuf);
					write(connected,sdbuf,strlen(sdbuf));
					bzero(sdbuf, 1024); 


					//file transfer
					fs = fopen(arg, "r");
					if(fs == NULL)
					{
						fprintf(stderr, "ERROR: File %s not found on server. (errno = %d)\n",arg, errno);
						exit(1);
					}

					bzero(sdbuf, 1024); 
					int fs_block_sz; 
					while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
					{
						//printf("here\n");
						if(write(connected, sdbuf, fs_block_sz) < 0)
						{
							fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", arg, errno);
							exit(1);
						}
						sdbuf[fs_block_sz]='\0';
						bzero(sdbuf, 1024);
					}
					printf("Ok sent to client!\n");
					fclose(fs);
				}
				else if(fu==1)
				{
					long mybytes;
					char size[1000];
					read(connected, size, 1024/*, 0*/);
					long siz=atoi(size);
					printf("\nsize=%ld\n",siz);
char sdbuf[1024];
						if(siz > 40000){
						bzero(sdbuf, 1024);
							strcpy(sdbuf,"FileUpload Deny!!");
						write(connected, sdbuf,strlen(sdbuf)); 
						continue;
						}
						bzero(sdbuf,1024);
						strcpy(sdbuf,"FileUpload Allow!");
						write(connected, sdbuf,strlen(sdbuf)); 
						bzero(sdbuf,1024);

					printf("[Client] Receiveing file from server and saving it ...\n");
					//FILE *fr = fopen("final.txt", "w");
					FILE *fr = fopen(args[2], "w");
					if(fr == NULL)
						printf("File %s Cannot be opened.\n", args[2]);
					else
					{
						bzero(recv_data, 1024); 
						int fr_block_sz = 0;
						mybytes=0;
						while((fr_block_sz = read(connected, recv_data, 1024/*, 0*/)) > 0)
						{
							mybytes+=fr_block_sz;
							recv_data[fr_block_sz]='\0';
							printf("%s\n",recv_data);
							fputs(recv_data,fr);
							bzero(recv_data, 1024);
							if (mybytes>=siz) 
							{
								break;
							}
						}
						if(fr_block_sz < 0)
						{
							if (errno == EAGAIN)
							{
								printf("recv() timed out.\n");
							}
							else
							{
								fprintf(stderr, "recv() failed due to errno = %d\n", errno);
							}
						}
						printf("Ok received from client!\n");
						fclose(fr);
					}

				}
				else if(ll==1)
				{

					char sdbuf[1024]; // Send buffer
					ok=fopen(".ll.txt","w");
					getfiles("./");
					fclose(ok);
					FILE *fs = fopen(".ll.txt", "r");
					fseek(fs, 0L, SEEK_END);
					long sz = ftell(fs);
					char len[1024];
					sprintf(len,"%ld",sz);
					write(connected,len,1024 );
					fclose(fs);
					printf("%s\n",len);
					fs = fopen(".ll.txt", "r");
					if(fs == NULL)
					{
						fprintf(stderr, "ERROR: File  not found on server. (errno = %d)\n", errno);
						exit(1);
					}
					bzero(sdbuf, 1024); 
					int fs_block_sz; 
					while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
					{
						if(write(connected, sdbuf, fs_block_sz) < 0)
						{
							fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", arg, errno);
							exit(1);
						}
						sdbuf[fs_block_sz]='\0';
						bzero(sdbuf, 1024);
					}
					printf("Ok sent to client!\n");
					fclose(fs);
				}
				else if(sl==1){
	char sdbuf[1024]; // Send buffer
					ok=fopen(".t.txt","w");
					timestamp("./",args);
					//getfiles("./");
					fclose(ok);
					FILE *fs = fopen(".t.txt", "r");
					fseek(fs, 0L, SEEK_END);
					long sz = ftell(fs);
					char len[1024];
					sprintf(len,"%ld",sz);
					write(connected,len,1024 );
					fclose(fs);
					printf("%s\n",len);
					fs = fopen(".t.txt", "r");
					if(fs == NULL)
					{
						fprintf(stderr, "ERROR: File  not found on server. (errno = %d)\n", errno);
						exit(1);
					}
					bzero(sdbuf, 1024); 
					int fs_block_sz; 
					if(sz!=0){
					while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
					{
						if(write(connected, sdbuf, fs_block_sz) < 0)
						{
							fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", arg, errno);
							exit(1);
						}
						sdbuf[fs_block_sz]='\0';
						bzero(sdbuf, 1024);
					}
					}
					printf("Ok sent to client!\n");
					fclose(fs);
				}


					

			}
			fflush(stdout);
		}
	}       
	close(sock);
	wait();
} 
void ClientProcess(){
	char *result=NULL;
	char *arg=NULL;
	int fd=0;
	int fu=0;
	int ll=0;
	int sl=0;
	int chk=0;
	int ver=0;
	int mybytes;
	int regex=0;
	FILE *h=fopen(".history","w");
	int sock, bytes_recieved;  
	char send_data[1024],recv_data[1024];
	struct hostent *host;
	struct sockaddr_in server_addr;
	host = gethostbyname(ipaddress);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
	int portno;
	portno=atoi(portnum);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portno);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8); 
	while(1){
		if (connect(sock, (struct sockaddr *)&server_addr,
					sizeof(struct sockaddr)) == -1) 
		{
			perror("Connect");
		}
		else{
			printf("Client is Connected now : \n");
			break;
		}
	}
	while(1)
	{
		fd=0;
		fu=0;
		arg=NULL;
		result=NULL;
		ll=0;
		sl=0;
		chk=0;
		ver=0;
		regex=0;
		char *a[100];
		printf("Enter ur query:\n");
		gets(send_data);
		fputs(send_data,h);
		fputs("\n",h);
		if (strcmp(send_data , "q") != 0 && strcmp(send_data , "Q") != 0){
			send(sock,send_data,strlen(send_data), 0); 
		}
		else
		{
			printf("Client is DisConnected now :/\n");
			send(sock,send_data,strlen(send_data), 0);   
			close(sock);
			break;
		}
		result = strtok(send_data, " \n" );
		printf("result=%s\n",result);
		int i=0;
		while(result !=NULL ){
			a[i]=result;
			result = strtok( NULL, " \n" );
			i++;
		}
//		char str[100];
//		strcpy(str,arg
		if(strcmp(a[0],"History")==0){
		//if(arg[0]=="History"){
			fclose(h);
				FILE *file = fopen (".history" , "r" );
				if (file != NULL)
				{   
					char line [1000];
					while(fgets(line,sizeof line,file)!= NULL) /* read a line from a file */
					{   
						fprintf(stdout,"%s",line); //print the file contents on stdout.
					}   
					fclose(file);
				}   
				else
				{   
					perror(".history"); //print the error message on stderr.
				}
				h=fopen(".history","a");
				continue;
			}

		if(strcmp(a[0],"FileDownload")==0){
			arg=a[1];
			fd=1;
		}
		else if(strcmp(a[0],"FileUpload")==0){
			arg=a[1];
			fu=1;
		}
		else if(strcmp(a[0],"IndexGet")==0){
			if(strcmp(a[1],"LongListing")==0){
				ll=1;
			}
			else if(strcmp(a[1],"ShortListing")==0){
				sl=1;
			}
			else if(strcmp(a[1],"RegEx")==0){
				regex=1;
			}
		}
		else if(strcmp(a[0],"FileHash")==0){
			if(strcmp(a[1],"Verify")==0){
				ver=1;
			}
			if(strcmp(a[1],"CheckAll")==0){
				chk=1;
			}
		}
		if(ver==1){
			bzero(recv_data, 1024); 
			int n= read(sock, recv_data,20);
			recv_data[n]='\0';
			if(strcmp(recv_data,"Sorry File not Found")==0){

			printf("%s\n",recv_data);
			continue;
			}
			printf("%s\n",recv_data);
			printf("%s\n",a[2]);
			bzero(recv_data, 1024); 
			n= read(sock, recv_data,32);
			recv_data[n]='\0';
			printf("md5  %s\n",recv_data);
			bzero(recv_data, 1024); 
			n= read(sock, recv_data,24);
			recv_data[n]='\0';
			printf("last modified time stamp  %s\n",recv_data);
			bzero(recv_data, 1024); 
		}
		if(chk==1){
			char size[1000];
			read(sock, size, 1024/*, 0*/);
			long siz=atoi(size);
			printf("size=%ld\n",siz);
			bzero(recv_data, 1024); 
			int fr_block_sz = 0;
			mybytes=0;
			while((fr_block_sz = read(sock, recv_data, 1024/*, 0*/)) > 0)
			{
				mybytes+=fr_block_sz;
				recv_data[fr_block_sz]='\0';
				printf("%s\n",recv_data);
				//		fputs(recv_data,fr);
				bzero(recv_data, 1024);
				if (mybytes>=siz) 
				{
					break;
				}
			}
			if(fr_block_sz < 0)
			{
				if (errno == EAGAIN)
				{
					printf("recv() timed out.\n");
				}
				else
				{
					fprintf(stderr, "recv() failed due to errno = %d\n", errno);
				}
			}
			printf("Ok received from server!\n");
			//			fclose(fr);
		}

if(regex==1){
	char size[1000];
			read(sock, size, 1024/*, 0*/);
			long siz=atoi(size);
			printf("size=%ld\n",siz);
			int fr_block_sz = 0;
			mybytes=0;

			while((fr_block_sz = read(sock, recv_data, 1024/*, 0*/)) > 0)
			{
				mybytes+=fr_block_sz;
				recv_data[fr_block_sz]='\0';
				printf("%s\n",recv_data);
				//		fputs(recv_data,fr);
				bzero(recv_data, 1024);
				if (mybytes>=siz) 
				{
					break;
				}
			}
			if(fr_block_sz < 0)
			{
				if (errno == EAGAIN)
				{
					printf("recv() timed out.\n");
				}
				else
				{
					fprintf(stderr, "recv() failed due to errno = %d\n", errno);
				}
			}
			printf("\nOk received from server!\n");
			//			fclose(fr);
		}
		if(fd==1){
			bzero(recv_data, 1024);
			int n=read(sock, recv_data, 20/*, 0*/);
			recv_data[n]='\0';
			if(strcmp(recv_data,"Sorry File not Found")==0){
				printf("%s\n",recv_data);
				continue;
			}
			printf("%s\n",recv_data);
			printf("ur download starting in 2 sec.........\n");
			bzero(recv_data, 1024);
			printf("filename=%s\n",arg);
			char size[1000];
			read(sock, size, 1024/*, 0*/);
			long siz=atoi(size);
			printf("size=%ld\n",siz);
			bzero(recv_data, 1024);
			n=read(sock, recv_data, 32/*, 0*/);
			recv_data[n]='\0';
			printf("md5hash %s\n",recv_data);
			bzero(recv_data, 1024);
			n=read(sock, recv_data, 24/*, 0*/);
			recv_data[n]='\0';
			printf("timestamp %s\n",recv_data);
			bzero(recv_data, 1024);
			printf("[Client] Receiveing file from Server and saving it ...\n");

			//FILE *fr = fopen("downloaded.txt", "w");
			FILE *fr = fopen(a[2], "w");
			if(fr == NULL)
				printf("File %s Cannot be opened.\n", a[2]);
			else
			{
				bzero(recv_data, 1024); 
				int fr_block_sz = 0;
				mybytes=0;
				while((fr_block_sz = read(sock, recv_data, 1024/*, 0*/)) > 0)
				{
					mybytes+=fr_block_sz;
					recv_data[fr_block_sz]='\0';
					//printf("%s\n",recv_data);    ///for printing on terminal
					fputs(recv_data,fr);
					bzero(recv_data, 1024);
					if (mybytes>=siz) 
					{
						break;
					}
				}
				if(fr_block_sz < 0)
				{
					if (errno == EAGAIN)
					{
						printf("recv() timed out.\n");
					}
					else
					{
						fprintf(stderr, "recv() failed due to errno = %d\n", errno);
					}
				}
				printf("\nOk received from server!\n");
				fclose(fr);
			}
		}
		else if(fu==1){
			//printf("\n file to be downloaded = %s " , arg);
			char sdbuf[1024]; // Send buffer
			FILE *fs = fopen(arg, "r");
			fseek(fs, 0L, SEEK_END);
			long sz = ftell(fs);
			char len[1024];

			sprintf(len,"%ld",sz);
			write(sock,len,1024 );
			fclose(fs);
			//printf("%s\n",len);
			
			//printf("\n file to be downloaded = %s " , arg);
		/*	FILE *fs = fopen(arg, "r");
			fseek(fs, 0L, SEEK_END);
			long sz = ftell(fs);
			char len[1024];
			sprintf(len,"%ld",sz);
			write(sock,len,1024 );
			fclose(fs);
			printf("%s\n",len);*/

			bzero(recv_data, 1024);
			int n=read(sock, recv_data, 17/*, 0*/);
			recv_data[n]='\0';
			if(strcmp(recv_data,"FileUpload Deny!!")==0){
				printf("%s\n",recv_data);
				continue;
			}
			printf("%s\n",recv_data);
			printf("[client] uploading %s to the server...", arg);
			fs = fopen(arg, "r");
			//FILE *fp=fopen("uploaded.txt","w");
			if(fs == NULL)
			{
				fprintf(stderr, "ERROR: File %s not found on server. (errno = %d)\n",arg, errno);
				exit(1);
			}

			bzero(sdbuf, 1024); 
			int fs_block_sz; 
			while((fs_block_sz = fread(sdbuf, sizeof(char), 1024, fs))>0)
			{
				//printf("here\n");
				//fwrite(sdbuf,sizeof(char),1024,fp);
				if(write(sock, sdbuf, fs_block_sz) < 0)
				{

					fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", arg, errno);
					exit(1);
				}
				sdbuf[fs_block_sz]='\0';
				bzero(sdbuf, 1024);
			}
			printf("Ok sent to server!\n");
			fclose(fs);
		//	fclose(fp);
		}
		else if(ll==1){

			char size[1000];
			read(sock, size, 1024/*, 0*/);
			long siz=atoi(size);
			printf("size=%ld\n",siz);
			bzero(recv_data, 1024); 
			int fr_block_sz = 0;
			mybytes=0;
			while((fr_block_sz = read(sock, recv_data, 1024/*, 0*/)) > 0)
			{
				mybytes+=fr_block_sz;
				recv_data[fr_block_sz]='\0';
				printf("%s\n",recv_data);
				//		fputs(recv_data,fr);
				bzero(recv_data, 1024);
				if (mybytes>=siz) 
				{
					break;
				}
			}
			if(fr_block_sz < 0)
			{
				if (errno == EAGAIN)
				{
					printf("recv() timed out.\n");
				}
				else
				{
					fprintf(stderr, "recv() failed due to errno = %d\n", errno);
				}
			}
			printf("\nOk received from server!\n");
		}
		else if(sl==1){
		char size[1000];
			read(sock, size, 1024/*, 0*/);
			long siz=atoi(size);
			printf("size=%ld\n",siz);
			bzero(recv_data, 1024); 
			int fr_block_sz = 0;
			mybytes=0;
			if(siz>0){
			while((fr_block_sz = read(sock, recv_data, 1024/*, 0*/)) > 0)
			{
				mybytes+=fr_block_sz;
				recv_data[fr_block_sz]='\0';
				printf("%s\n",recv_data);
				//		fputs(recv_data,fr);
				bzero(recv_data, 1024);
				if (mybytes>=siz) 
				{
					break;
				}
			}
			if(fr_block_sz < 0)
			{
				if (errno == EAGAIN)
				{
					printf("recv() timed out.\n");
				}
				else
				{
					fprintf(stderr, "recv() failed due to errno = %d\n", errno);
				}
			}
			}
			printf("\nOk received from server!\n");
		}
}
fclose(h);
}

