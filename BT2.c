#include <stdio.h>

struct Account {
    int user_id;
    char username[50];
    int plan_type;
    int days_overdue;
    int active_devices;
};

int main() {
    int n, i;
    int total_revenue = 0;
    int downgraded_count = 0;

    printf("Nhap so luong tai khoan (1 - 100): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("So lượng tài khoản khong hop le!\n");
        return 1;
    }

    struct Account user_list[100];

    for (i = 0; i < n; i++) {
        printf("\nNhap thong tin cho tai khoan thu %d:\n", i + 1);
        
        printf("Ma tai khoan: ");
        scanf("%d", &user_list[i].user_id);
        
        printf("Ten tai khoan: ");
        scanf("%s", user_list[i].username);

        do {
            printf("Loai goi hien tai (1: Free, 2: Personal, 3: Family): ");
            scanf("%d", &user_list[i].plan_type);
            if (user_list[i].plan_type < 1 || user_list[i].plan_type > 3) {
                printf("Loai goi khong hop le! Vui long nhap lai (1-3).\n");
            }
        } while (user_list[i].plan_type < 1 || user_list[i].plan_type > 3);

        do {
            printf("So ngay no cuoc (>= 0): ");
            scanf("%d", &user_list[i].days_overdue);
            if (user_list[i].days_overdue < 0) {
                printf("So ngay no cuoc khong duoc am! Vui long nhap lai.\n");
            }
        } while (user_list[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi (> 0): ");
            scanf("%d", &user_list[i].active_devices);
            if (user_list[i].active_devices <= 0) {
                printf("So thiet bi phai lon hon 0! Vui long nhap lai.\n");
            }
        } while (user_list[i].active_devices <= 0);
    }

    for (i = 0; i < n; i++) {
        if (user_list[i].days_overdue >= 3) {
            if (user_list[i].plan_type != 1) {
                downgraded_count++;
            }
            user_list[i].plan_type = 1;
        }
    }

    printf("\n=================== BANG BAO CAO SAU DOI SOAT ===================\n");
    printf("%-10s %-15s %-10s %-12s %-15s %-18s\n", "MA TK", "TEN TK", "MA GOI", "SO THIET BI", "SO NGAY NO", "PHI THUC THU");
    printf("---------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        int service_fee = 0;

        if (user_list[i].plan_type == 2) {
            service_fee = 120000;
            if (user_list[i].active_devices > 1) {
                service_fee += (user_list[i].active_devices - 1) * 30000;
            }
        } else if (user_list[i].plan_type == 3) {
            service_fee = 250000;
        } else {
            service_fee = 0;
        }

        total_revenue += service_fee;

        printf("%-10d %-15s %-10d %-12d %-15d %-18d\n",
               user_list[i].user_id,
               user_list[i].username,
               user_list[i].plan_type,
               user_list[i].active_devices,
               user_list[i].days_overdue,
               service_fee);
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("Tong doanh thu thuc te thu duoc trong ky: %d VND\n", total_revenue);
    printf("Tong so tai khoan bi ha cap ve goi Free: %d\n", downgraded_count);

    return 0;
}