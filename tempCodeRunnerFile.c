// Nama: Rorencia Fadlyla
// NPM : 23081010124
// Kelas: Strukdat E081

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAHASISWA 20

struct node {
    char nama[100];
    char jenis_kelamin;
    struct node *next;
};

typedef struct node node;

void tambahMahasiswa(node **pList);
void keluarMahasiswa(node **pList);
void pisahLingkaran(node **pList);

int main() {
    node *pList = NULL;
    int pilih;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Mahasiswa keluar lingkaran\n");
        printf("3. Pisahkan lingkaran Mahasiswa\n");
        printf("0. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            tambahMahasiswa(&pList);
        } else if (pilih == 2) {
            keluarMahasiswa(&pList);
        } else if (pilih == 3) {
            pisahLingkaran(&pList);
        }

    } while (pilih != 0);

    return 0;
}

void tambahMahasiswa(node **pList) {
    char nama[100];
    char jenis_kelamin;
    node *pNew, *pcur;

    int count = 0;
    if (*pList != NULL) {
        pcur = *pList;
        do {
            count++;
            pcur = pcur->next;
        } while (pcur != *pList);
    }

    if (count >= MAX_MAHASISWA) {
        printf("Lingkaran sudah penuh, tidak bisa menambah mahasiswa.\n");
        return;
    }

    printf("Masukkan nama Mahasiswa: ");
    scanf("%s", nama);
    printf("Masukkan jenis kelamin (L/P): ");
    scanf(" %c", &jenis_kelamin);

    // kondisi Cindy
    if (strcmp(nama, "Cindy") == 0) {
        int wanita_count = 0;
        pcur = *pList;

        if (*pList != NULL) {
            do {
                if (pcur->jenis_kelamin == 'P') {
                    wanita_count++;
                }
                pcur = pcur->next;
            } while (pcur != *pList);
        }

        if (wanita_count < 2) {
            printf("Cindy tidak dapat bergabung karena harus ada minimal 2 mahasiswi lain.\n");
            return;
        }
    }

    // kondisi Irsyad atau Arsyad
    if (strcmp(nama, "Irsyad") == 0 || strcmp(nama, "Arsyad") == 0) {
        node *pNew1 = (node *)malloc(sizeof(node));
        if (pNew1 == NULL) {
            printf("Alokasi memori gagal.\n");
            return;
        }
        strcpy(pNew1->nama, strcmp(nama, "Irsyad") == 0 ? "Irsyad" : "Arsyad");
        pNew1->jenis_kelamin = 'L';

        if (*pList == NULL) {
            pNew1->next = pNew1;
            *pList = pNew1;
        } else {
            pcur = *pList;
            while (pcur->next != *pList) {
                pcur = pcur->next;
            }
            pNew1->next = *pList;
            pcur->next = pNew1;
        }

        printf("Data berhasil ditambahkan: %s, '%c'.\n", pNew1->nama, pNew1->jenis_kelamin);

        if (strcmp(nama, "Irsyad") == 0) {
            node *pNew2 = (node *)malloc(sizeof(node));
            if (pNew2 == NULL) {
                printf("Alokasi memori gagal.\n");
                return;
            }
            strcpy(pNew2->nama, "Arsyad");
            pNew2->jenis_kelamin = 'L';
            pcur = *pList;

            while (pcur->next != *pList) {
                pcur = pcur->next;
            }
            pNew2->next = *pList;
            pcur->next = pNew2;
            printf("Data berhasil ditambahkan: %s, '%c'.\n", pNew2->nama, pNew2->jenis_kelamin);
        } else if (strcmp(nama, "Arsyad") == 0) {
            node *pNew2 = (node *)malloc(sizeof(node));
            if (pNew2 == NULL) {
                printf("Alokasi memori gagal.\n");
                return;
            }
            strcpy(pNew2->nama, "Irsyad");
            pNew2->jenis_kelamin = 'L';
            pcur = *pList;

            while (pcur->next != *pList) {
                pcur = pcur->next;
            }
            pNew2->next = *pList;
            pcur->next = pNew2;
            printf("Data berhasil ditambahkan: %s, '%c'.\n", pNew2->nama, pNew2->jenis_kelamin);
        }

        return;
    }

    // Tambahkan mahasiswa biasa
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal.\n");
        return;
    }

    strcpy(pNew->nama, nama);
    pNew->jenis_kelamin = jenis_kelamin;

    if (*pList == NULL) {
        pNew->next = pNew;
        *pList = pNew;
    } else {
        pcur = *pList;
        while (pcur->next != *pList) {
            pcur = pcur->next;
        }
        pNew->next = *pList;
        pcur->next = pNew;
    }

    printf("Data berhasil ditambahkan: %s, '%c'.\n", pNew->nama, pNew->jenis_kelamin);
}

void keluarMahasiswa(node **pList) {
    char nama[100];
    node *pcur, *ppre;

    if (*pList == NULL) {
        printf("\nTidak ada mahasiswa dalam lingkaran.\n");
        return;
    }

    printf("Nama mahasiswa yang akan keluar dari lingkaran: ");
    scanf("%s", nama);

    pcur = *pList;
    ppre = NULL;

    do {
        if (strcmp(pcur->nama, nama) == 0) {
            break;
        }
        ppre = pcur;
        pcur = pcur->next;
    } while (pcur != *pList);

    if (pcur == *pList && strcmp(pcur->nama, nama) != 0) {
        printf("\nMahasiswa tidak ada dalam lingkaran.\n");
        return;
    }

    // kondisi Irsyad dan Arsyad
    if (strcmp(pcur->nama, "Irsyad") == 0 || strcmp(pcur->nama, "Arsyad") == 0) {
        char *saudara = strcmp(pcur->nama, "Irsyad") == 0 ? "Arsyad" : "Irsyad";
        printf("%s dan %s keluar dari lingkaran.\n", pcur->nama, saudara);

        node *temp = pcur->next;
        while (temp != pcur) {
            if (strcmp(temp->nama, saudara) == 0) {
                break;
            }
            temp = temp->next;
        }

        if (temp == pcur) {
            if (pcur == *pList) {
                if (pcur->next == *pList) {
                    free(pcur);
                    *pList = NULL;
                } else {
                    ppre = *pList;
                    while (ppre->next != *pList) {
                        ppre = ppre->next;
                    }
                    ppre->next = pcur->next;
                    free(pcur);
                    free(temp);
                    *pList = ppre->next;
                }
            } else {
                ppre->next = pcur->next;
                free(pcur);
                free(temp);
            }
        }
        return;
    }

    if (pcur == *pList) {
        if (pcur->next == *pList) {
            free(pcur);
            *pList = NULL;
        } else {
            ppre = *pList;
            while (ppre->next != *pList) {
                ppre = ppre->next;
            }
            if (strcmp(pcur->nama, "Cindy") == 0) {
                // Jika Cindy akan keluar
                printf("Cindy keluar dari lingkaran.\n");
            }
            ppre->next = pcur->next;
            *pList = pcur->next;
            free(pcur);
        }
    } else {
        ppre->next = pcur->next;
        free(pcur);
    }

    printf("Mahasiswa %s keluar dari lingkaran.\n", nama);
}

void pisahLingkaran(node **pList) {
    if (*pList == NULL) {
        printf("List kosong, tidak ada mahasiswa.\n");
        return;
    }

    node *pCur = *pList;        
    node *headPria = NULL;      
    node *headWanita = NULL;    

    do {
        node *pNew = (node *)malloc(sizeof(node));
        if (pNew == NULL) {
            printf("Alokasi memori gagal.\n");
            return;
        }

        strcpy(pNew->nama, pCur->nama);
        pNew->jenis_kelamin = pCur->jenis_kelamin;

        if (pCur->jenis_kelamin == 'L') {
            if (headPria == NULL) {
                headPria = pNew;
                pNew->next = headPria; 
            } else {
                node *pLastPria = headPria;
                while (pLastPria->next != headPria) {
                    pLastPria = pLastPria->next;
                }
                pLastPria->next = pNew; 
                pNew->next = headPria; 
            }
        } else {
            if (headWanita == NULL) {
                headWanita = pNew;
                pNew->next = headWanita; 
            } else {
                node *pLastWanita = headWanita;
                while (pLastWanita->next != headWanita) {
                    pLastWanita = pLastWanita->next;
                }
                pLastWanita->next = pNew; 
                pNew->next = headWanita; 
            }
        }

        pCur = pCur->next;

    } while (pCur != *pList);


    printf("\nLingkaran Mahasiswa:\n");
    pCur = headPria;
    if (pCur != NULL) {
        do {
            printf("%s (%c) ", pCur->nama, pCur->jenis_kelamin);
            pCur = pCur->next;
        } while (pCur != headPria);
    } else {
        printf("Tidak ada mahasiswa pria.\n");
    }

    printf("\nLingkaran Mahasiswi:\n");
    pCur = headWanita;
    if (pCur != NULL) {
        do {
            printf("%s (%c) ", pCur->nama, pCur->jenis_kelamin);
            pCur = pCur->next;
        } while (pCur != headWanita);
    } else {
        printf("Tidak ada mahasiswa wanita.\n");
    }

    // Menghapus pemisahan list untuk mencegah kebocoran memori
    while (headPria != NULL) {
        node *temp = headPria;
        headPria = headPria->next;
        free(temp);
    }

    while (headWanita != NULL) {
        node *temp = headWanita;
        headWanita = headWanita->next;
        free(temp);
    }
}

