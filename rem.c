/*
 * rem - A minimal, ultra-lightweight command-line snippet manager
 * Copyright (C) 2026 aresthebellator
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_L 1024
#define RESET "\033[0m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"


void show_rem()
{
  printf("\n");
  printf(YELLOW " HOW TO USE: \n" RESET);
  printf("  rem" CYAN " add " RESET "\"title\" \"command\" -> THIS FUNCTION ADDS A NEW REM\n");
  printf("  rem" CYAN " list " RESET  "-> THIS FUNCTION SHOWS ALL REMS\n");
  printf("  rem" CYAN " find " RESET "\"title\"  -> FINDS A SPECIFIC REM\n");
  printf("  rem" CYAN " help " RESET "--> SHOW THE PATH WHERE YOU CAN EDIT THE TXT FILE\n");
  printf("  rem" CYAN " edit " RESET "\"search_term\" \"new_title\" \"new_cmd\" --> EDIT A REM\n");
  printf("  rem" CYAN " remove " RESET "--> REMOVE A REM\n");
}

int main(int argc, char *argv[])
{
  char file_path[MAX_L];
    const char *home_dir = getenv("HOME");
  if(home_dir == NULL)
  {
    home_dir = getenv("USERPROFILE");
    if(home_dir == NULL)
    {
      printf(RED "ERROR: Cannot determine the Home directory.\n" RESET);
    }
  }
  snprintf(file_path,sizeof(file_path),"%s/%s",home_dir,"RemC.txt");

  if(argc < 2)
  {
    show_rem();
    return 1;
  }

  
  if(strcmp(argv[1], "add") == 0)
  {
    if(argc != 4)
    {
      printf(RED "ERROR: YOU NEED TO ADD A TITLE AND A COMMAND.\n" RESET);
      return 1;
    }
    
    FILE *file = fopen(file_path, "a");
    if(file == NULL)
    {
      printf(RED "Error opening file.\n" RESET);
      return 1;
    }
    fprintf(file, "%s | %s\n", argv[2], argv[3]);
    fclose(file);
    printf(YELLOW "REM SAVED SUCCESSFULLY\n" RESET);
    }
  
  else if(strcmp(argv[1], "list") == 0)
  {
    FILE *file = fopen(file_path, "r");
    if(file == NULL)
    {
      printf(RED "No REM saved, or file does not exist.\n" RESET);
      return 1;
    }
    char line[MAX_L];
    printf(YELLOW "\n--- YOUR REMS ---\n" RESET);
    while(fgets(line, sizeof(line), file) != NULL)
    {
      printf("- %s", line);
    }
    
    fclose(file);
  }
  
  else if(strcmp(argv[1], "find") == 0)
  {
    if(argc != 3)
    {
      printf(RED "ERROR: ENTER THE SEARCH TERM.\n" RESET);
      return 1;
    }
    
    FILE *file = fopen(file_path, "r");
    if(file == NULL)
    {
      printf(RED "No REM saved, or file does not exist.\n" RESET);
      return 1;
    }

    char line[MAX_L];
    int found = 0;
    char *search_term = argv[2];
    
    printf(YELLOW "\n--- SEARCH RESULTS FOR: '%s' ---\n" RESET, search_term);
    while(fgets(line, sizeof(line), file) != NULL)
    {
      if(strstr(line, search_term) != NULL)
      {
        printf("- %s", line);
        found++;
      }
    }
    
    if(found == 0)
    {
      printf(RED "No results found.\n" RESET);
    }
    
    fclose(file);
  }
  
  else if(strcmp(argv[1],"help") == 0)
  {
    const char *home = getenv("HOME");
    if(home == NULL)
    {
      printf(RED "ERROR: I cannot find the Home directory.\n" RESET);
      return 1;
    }
    char full_path[512];
    const char *file_name = "RemC.txt";
    snprintf(full_path,sizeof(full_path),"%s/%s",home, file_name);
    printf("PATH: %s\n",full_path);
    return 0;
  }
  
  else if(strcmp(argv[1],"edit") == 0)
  {
    if(argc != 5)
    {
      printf(RED "ERROR: YOU NEED TO PROVIDE SEARCH TERM, NEW TITLE AND NEW COMMAND.\n" RESET);
      printf(YELLOW "HOW TO USE: rem edit \"search_term\" \"new_title\" \"new_command\"\n" RESET);
      return 1;
    } 
    char temp_path[MAX_L];
    snprintf(temp_path,sizeof(temp_path),"%s/%s",home_dir,"RemC_temp.txt");
    FILE *file = fopen(file_path,"r");
    if(file == NULL)
    {
      printf(RED "NO REM SAVED, OR FILE DOES NOT EXIST.\n" RESET);
      return 1;
    }
    FILE *temp = fopen(temp_path,"w");
    if(temp == NULL)
    {
      printf(RED "Error creating temporary file.\n" RESET);
      fclose(file);
      return 1;
    }
    char line[MAX_L];
    int f = 0;
    char *search_term = argv[2];
    char *new_title = argv[3];
    char *new_command = argv[4];
    while(fgets(line,sizeof(line),file) != NULL)
    {
      if(!f && strstr(line,search_term) != NULL)
      {
        fprintf(temp,"%s | %s\n",new_title,new_command);
        f = 1;
      }
      else
      {
        fputs(line,temp);
      }
    }
    fclose(file);
    fclose(temp);
    if(f)
    {
      remove(file_path);
      rename(temp_path,file_path);
      printf(YELLOW "REM EDITED SUCCESSFULLY\n" RESET);
    }
    else
    {
      remove(temp_path);
      printf(RED "NO MATCHING REM FOUND TO EDIT.\n"RESET);
    }
  }
  
  else if(strcmp(argv[1],"remove") == 0)
  {
    if(argc != 3)
    {
      printf(RED "ERROR: YOU NEED TO PROVIDE THE SEARCH TERM TO REMOVE.\n" RESET);
      printf(YELLOW "USAGE: rem remove \"search_term\"\"\n" RESET);
      return 1;
    }
    
    char temp_path[MAX_L];
    snprintf(temp_path,sizeof(temp_path),"%s/%s",home_dir,"RemC_temp.txt");
    FILE *file = fopen(file_path,"r");
    if(file == NULL)
    {
      printf(RED "NO REM SAVED, OR FILE DOES NOT EXIST.\n" RESET);
      return 1;
    }
    FILE *temp = fopen(temp_path,"w");
    if(temp == NULL)
    {
      printf(RED "Error creating temporary file.\n" RESET);
      fclose(file);
      return 1;
    }

    char line[MAX_L];
    int removed = 0;
    char *r_command = argv[2];
    while(fgets(line,sizeof(line),file) != NULL)
    {
      if(strstr(line,r_command) == NULL)
      {
        fputs(line,temp);
      }
      else
      {
          removed++;
      }
    }
    fclose(file);
    fclose(temp);
    if(removed > 0)
    {
      remove(file_path);
      rename(temp_path,file_path);
      printf(YELLOW "REM EDITED SUCCESSFULLY\n" RESET);
    }
    else
    {
      remove(temp_path);
      printf(RED "NO MATCHING REM FOUND TO REMOVE. \n" RESET);
    }
  }

  else
  {
    printf(RED "Error: Command not found: %s\n" RESET, argv[1]);
    show_rem();
  }

  return 0;
}
