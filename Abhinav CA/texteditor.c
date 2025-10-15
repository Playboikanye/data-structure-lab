#include <stdio.h>
#include <string.h>
int main() {
char text[500];
char find[50];
char replace[50];
char newText[1000];
int i = 0, j = 0;
int findLen, replaceLen;
printf("Enter the text:\n");
fgets(text, sizeof(text), stdin);
text[strcspn(text, "\n")] = '\0';
printf("Enter the word to find:\n");
fgets(find, sizeof(find), stdin);
find[strcspn(find, "\n")] = '\0';
printf("Enter the word to replace with:\n");
fgets(replace, sizeof(replace), stdin);
replace[strcspn(replace, "\n")] = '\0';
findLen = strlen(find);
replaceLen = strlen(replace);
while (text[i] != '\0') {
if (strncmp(&text[i], find, findLen) == 0) {
for (int k = 0; k < replaceLen; k++) {
newText[j++] = replace[k];
}
i += findLen;
} else {
newText[j++] = text[i++];
}
}
newText[j] = '\0';
printf("\nOriginal text:\n%s\n", text);
printf("\nText after find and replace:\n%s\n", newText);
return 0;
}