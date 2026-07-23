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

#define FILE_NAME "RemC.txt"
#define MAX_L 1024
#define RESET "\033[0m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"


void show_rem()
{
  printf(YELLOW "HOW TO USE: \n" RESET);
  printf("  ./rem" CYAN " add " RESET "\"title\" \"command\" -> THIS FUNCTION ADDS A NEW REM\n");
  printf("  ./rem" CYAN " list " RESET  "-> THIS FUNCTION SHOWS ALL REMS\n");
  printf("  ./rem" CYAN " find " RESET "\"title\"  -> FINDS A SPECIFIC REM\n");
}

int main(int argc, char *argv[])
{
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
    
    FILE *file = fopen(FILE_NAME, "a");
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
    FILE *file = fopen(FILE_NAME, "r");
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
    
    FILE *file = fopen(FILE_NAME, "r");
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
  
  else
  {
    printf(RED "Error: Command not found: %s\n" RESET, argv[1]);
    show_rem();
  }

  return 0;
}
