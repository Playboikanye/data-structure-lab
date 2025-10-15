#include <stdio.h>
int main() {
int arr[100], n, key, low, high, mid, flag = 0, comparisons = 0;
printf("Enter number of elements: ");
scanf("%d", &n);
printf("Enter elements in sorted order:\n");
for (int i = 0; i < n; i++)
scanf("%d", &arr[i]);
printf("Enter element to search: ");
scanf("%d", &key);
low = 0;
high = n - 1;
while (low <= high) {
mid = (low + high) / 2;
comparisons++;
if (arr[mid] == key) {
printf("Element %d found at position %d.\n", key, mid + 1);
flag = 1;
break;
}
else if (key < arr[mid])
high = mid - 1;
else
low = mid + 1;
}
if (flag == 0)
printf("Element not found.\n");
printf("\n--- COMPLEXITY ANALYSIS ---\n");
if (comparisons == 1)
printf("Best Case: Element found at mid in first comparison → O(1)\n");
else if (flag == 1)
printf("Average Case: Element found after %d comparisons → O(log n)\n",
comparisons);
else
printf("Worst Case: Element not found after %d comparisons → O(log n)\n",
comparisons);
printf("Total Comparisons Made: %d\n", comparisons);
printf("Space Complexity: O(1)\n");
return 0;
}