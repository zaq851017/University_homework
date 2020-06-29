// ConsoleApplication1.cpp: 定義主控台應用程式的進入點。
//
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include <stdlib.h> 
#include <math.h>
struct instruct {
	int inode;
	int name;
	int min;
	int max;
	unsigned long long int inode_num;
	char file_name[30000];
	double min_num;
	double max_num;
};
struct instruct sta;
int is_test(char *path, struct stat s)
{
	if (sta.inode && s.st_ino != sta.inode_num)
		return 0;
	if (sta.name && strcmp(path,sta.file_name)!=0 )
		return 0;
	if (sta.min && (double)(s.st_size / pow(2,20)) < sta.min_num)
		return 0;
	if (sta.max && (double)(s.st_size / pow(2,20))> sta.max_num)
		return 0;
	return 1;
}

void find_dir(char *file_path) {
	DIR *dir;
	struct dirent *read_dir;
	struct stat dir_s;
	dir = opendir(file_path);
	char c_file[30000];
	strcpy(c_file,file_path);
	if(c_file[strlen(c_file)-1] != '/')
		strcat(c_file,"/");
	if(dir != NULL){
		while ( (read_dir = readdir(dir)) != NULL) {
		if (strcmp(read_dir->d_name, ".") == 0)
			continue;
		if (strcmp(read_dir->d_name, "..") == 0)
			continue;
		char a_file[30000];
		strcpy(a_file,c_file);
		strcat(a_file,read_dir->d_name);
		stat((const char *)a_file, &dir_s);
		
		if (S_ISREG(dir_s.st_mode)) {
			if (is_test(read_dir->d_name, dir_s))
				printf("%s %lu %lf MB\n", a_file, dir_s.st_ino, (double)(dir_s.st_size / pow(2,20)));
		}

		if (S_ISDIR(dir_s.st_mode)) {
			if (is_test(read_dir->d_name, dir_s))
				printf("%s %lu %lf MB\n", a_file , dir_s.st_ino, (double)(dir_s.st_size / pow(2,20)));
			
			char b_file[30000];
			strcpy(b_file,a_file);
			strcat(b_file,"/");
			find_dir(b_file);
		}



	  }
		
	}
	
	closedir(dir);

}
int main(int argc,char **argv)
{
	sta.inode = sta.name = sta.min = sta.max = 0;
	sta.inode_num = -1;
	for (int i = 0; i < 30000; i++)
		sta.file_name[i] = 0;
	sta.min_num = -1;
	sta.max_num = -1;

	for (int i = 1; i < argc; i++) { // i=1 is file_name
		char input[30000];
		strcpy(input, argv[i]);
		if (strcmp(input, "-inode") == 0) {
			sta.inode = 1;
			sta.inode_num = atoll(argv[i + 1]);
			i = i + 1;
		}
		else if (strcmp(input, "-name") == 0) {
			sta.name = 1;
			strcpy(sta.file_name, argv[i+1]);
			i = i + 1;
		}
		else if (strcmp(input, "-size_min" )== 0) {
			sta.min = 1;
			sta.min_num = atof(argv[i + 1]);
			i = i + 1;
		}
		else if (strcmp(input, "-size_max") == 0) {
			sta.max = 1;
			sta.max_num = atof(argv[i + 1]);
			i = i + 1;
		}
	}

	find_dir(argv[1]);

    return 0;
}

