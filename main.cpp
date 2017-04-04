#include <windows.h>

#include <stdio.h>

int GetModuleDirectory(HINSTANCE module, char* buffer, int buffer_length)
{
	int module_path_length = GetModuleFileName(module, buffer, buffer_length);
	int original_length = module_path_length;

	if(module_path_length)
	{
		for(int i = module_path_length - 1; i >= 0; i--)
		{
			if(buffer[i] == '\\')
			{
				module_path_length = i + 1;
				break;
			}
		}
	}

	for(int i = module_path_length; i <= original_length; i++)
	{
		buffer[i] = 0;
	}

	return module_path_length;
}

bool CopyStringIntoBuffer(char* string, char* buffer)
{
	int string_length = strlen(string);

	for(int i = 0; i <= string_length; i++)
	{
		buffer[i] = string[i];
	}
}

int main()
{
	char exe_path[MAX_PATH];

	int exe_path_length = GetModuleDirectory(0, exe_path, MAX_PATH);

	CopyStringIntoBuffer("gitignores\\default.gitignore", exe_path + exe_path_length);

	bool copy_success = CopyFile(exe_path, ".gitignore", true);

	if(copy_success)
	{
		printf("Successfully created .gitignore file.");
	}
	else
	{
		while(true)
		{
			printf("Creating a .gitignore file here would override an already existing file. Would you like to continue? (y/n): ", exe_path);

			char read_chars[1];

			gets(read_chars);

			char read_char = read_chars[0];

			if(read_char == 'y' || read_char == 'Y')
			{
				bool copy_success = CopyFile(exe_path, ".gitignore", false);

				if(copy_success)
				{
					printf("Successfully created .gitignore file.");
				}
				else
				{
					printf("Failed to create .gitignore file.");
				}

				break;
			}
			else if(read_char == 'n' || read_char == 'N')
			{
				printf("Canceled .gitignore creation.");

				break;
			}
		}
	}
}