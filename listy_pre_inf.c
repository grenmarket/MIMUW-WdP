#include <stddef.h>

typedef struct Tlista {
    int w;
    struct Tlista *nast;
} Tlista;

/*
Drzewo d nazwiemy ścieżkowym, jeżeli każdy węzeł ma co najwyżej jednego
potomka. Napisz funkcję bool istnieje(TLista* pre, TLista* inf), która
przekaże w wyniku TRUE jeżeli istnieje drzewo ścieżkowe o obiegu
prefiksowym od lewej do prawej równym pre zawierające poddrzewo o obiegu
infiksowym od lewej do prawej równym inf, oraz przekaże FALSE w przeciwnym
przypadku. Należy założyć, że obie listy zawierają liczby całkowite i są
różnowartościowe.
 */

#include <stdbool.h>

int dlugosc(Tlista *lista) {

}

void odwroc(Tlista **lista) {

}

bool istnieje(Tlista* pre, Tlista* inf) {
    int d_pre = dlugosc(pre);
    int d_inf = dlugosc(inf);
    bool ok = false;
    if (d_inf <= d_pre) {
        for (int i = 0; i < d_pre - d_inf; i++) {
            pre = pre->nast;
        }
        odwroc(&pre);
        if (pre == NULL) {
            ok = true;
        } else {
            int ost = pre->w;
            // rozbić na "bitoniczną" listę w dwa kierunki od pre[0], dostajemy:
            Tlista *l1, *l2;
        }
    }
    return ok;
}
