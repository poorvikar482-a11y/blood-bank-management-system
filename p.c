#include <stdio.h>
#include <string.h>
struct Donor {
    int id;
    char name[50];
    int age;
    char bloodGroup[5];
    long long int phone;
};

struct Donor d[100];
int count = 0;
int stock[8] = {0};

char *bg[8] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

void saveDonors() {
    FILE *f = fopen("donors.txt", "w");
    if (f == NULL)
        return;

    fprintf(f, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d\n%s\n%d\n%s\n%lld\n",
        d[i].id, d[i].name, d[i].age,
        d[i].bloodGroup, d[i].phone);
    }

    fclose(f);
}

void loadDonors() {
    FILE *f = fopen("donors.txt", "r");
    if (f == NULL)
        return;

    fscanf(f, "%d", &count);

    if (count > 100)
        count = 100;

    for (int i = 0; i < count; i++) {
        fscanf(f, "%d\n", &d[i].id);
        fgets(d[i].name, 50, f);
        d[i].name[strcspn(d[i].name, "\n")] = '\0';
        fscanf(f, "%d", &d[i].age);
        fscanf(f, "%4s", d[i].bloodGroup);
        fscanf(f, "%lld", &d[i].phone);
    }

    fclose(f);
}

void saveStock() {
    FILE *f = fopen("stock.txt", "w");
    if (f == NULL)
        return;

    for (int i = 0; i < 8; i++) {
        fprintf(f, "%s %d\n", bg[i], stock[i]);
    }

    fclose(f);
}

void loadStock() {
    FILE *f = fopen("stock.txt", "r");
    if (f == NULL)
        return;

    char blood[5];
    int units;

    while (fscanf(f, "%4s %d", blood, &units) == 2) {
        for (int i = 0; i < 8; i++) {
            if (strcmp(blood, bg[i]) == 0) {
                stock[i] = units;
                break;
            }
        }
    }

    fclose(f);
}

void registerDonor() {
    if (count >= 100) {
        printf("Donor list is full!\n");
        return;
    }

    d[count].id = count + 1;

    printf("Enter Name: ");
    scanf(" %49[^\n]", d[count].name);

    printf("Enter Age: ");
    scanf("%d", &d[count].age);

    if (d[count].age < 18 || d[count].age > 65) {
        printf("Invalid Age!\n");
        return;
    }

    printf("Enter Blood Group: ");
    scanf("%4s", d[count].bloodGroup);

    int valid = 0;

    for (int i = 0; i < 8; i++) {
        if (strcmp(d[count].bloodGroup, bg[i]) == 0) {
            valid = 1;
            break;
        }
    }

    if (valid == 0) {
        printf("Invalid Blood Group!\n");
        return;
    }

    printf("Enter Phone Number: ");
    scanf("%lld", &d[count].phone);

    count++;
    saveDonors();

    printf("Donor Registered Successfully!\n");
}

void updateStock() {
    char blood[5];
    int units, found = 0;

    printf("Enter Blood Group: ");
    scanf("%4s", blood);

    printf("Enter Units: ");
    scanf("%d", &units);

    if (units <= 0) {
        printf("Invalid Units!\n");
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (strcmp(blood, bg[i]) == 0) {
            stock[i] = stock[i] + units;
            found = 1;
            saveStock();

            printf("Stock Updated\n");
            printf("Available Units: %d\n", stock[i]);
            break;
        }
    }

    if (found == 0)
        printf("Invalid Blood Group!\n");
}

void searchBloodGroup() {
    char blood[5];
    int found = 0;

    printf("Enter Blood Group: ");
    scanf("%4s", blood);

    for (int i = 0; i < count; i++) {
        if (strcmp(blood, d[i].bloodGroup) == 0) {
            printf("\nID: %d\n", d[i].id);
            printf("Name: %s\n", d[i].name);
            printf("Age: %d\n", d[i].age);
            printf("Blood Group: %s\n", d[i].bloodGroup);
            printf("Phone: %lld\n", d[i].phone);
            found = 1;
        }
    }

    if (found == 0)
        printf("Donor Not Found!\n");
}

void issueBlood() {
    char blood[5];
    int units, found = 0;

    printf("Enter Blood Group: ");
    scanf("%4s", blood);

    printf("Enter Units Required: ");
    scanf("%d", &units);

    if (units <= 0) {
        printf("Invalid Units!\n");
        return;
    }

    for (int i = 0; i < 8; i++) {
        if (strcmp(blood, bg[i]) == 0) {
            found = 1;

            if (stock[i] >= units) {
                stock[i] = stock[i] - units;
                saveStock();

                printf("Blood Issued Successfully!\n");
                printf("Remaining Units: %d\n", stock[i]);
            }
            else {
                printf("Not Enough Blood Stock!\n");
            }

            break;
        }
    }

    if (found == 0)
        printf("Invalid Blood Group!\n");
}

void donorReport() {
    if (count == 0) {
        printf("No Donors Available!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", d[i].id);
        printf("Name: %s\n", d[i].name);
        printf("Age: %d\n", d[i].age);
        printf("Blood Group: %s\n", d[i].bloodGroup);
        printf("Phone: %lld\n", d[i].phone);
    }
}

void showStock() {
    printf("\nBlood Group\tUnits\n");

    for (int i = 0; i < 8; i++) {
        printf("%s\t\t%d\n", bg[i], stock[i]);
    }
}

int main() {
    int choice;

    loadDonors();
    loadStock();

    while (1) {
        printf("\nBLOOD BANK MANAGEMENT SYSTEM\n");
        printf("1. Donor Registration\n");
        printf("2. Update Blood Stock\n");
        printf("3. Search Blood Group\n");
        printf("4. Issue Blood\n");
        printf("5. Donor Report\n");
        printf("6. Show Blood Stock\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerDonor();
                break;
            case 2:
                updateStock();
                break;
            case 3:
                searchBloodGroup();
                break;
            case 4:
                issueBlood();
                break;
            case 5:
                donorReport();
                break;
            case 6:
                showStock();
                break;
            case 7:
                printf("Thank You\n");
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    }
}

