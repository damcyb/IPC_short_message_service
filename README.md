# IPC_short_message_service

#Instrukcja kompilacji i uruchomienia:

    W celu skompilowania i uruchomienia plikow nalezy w terminalu, w katalogu z plikami, uzyc komendy:
        - make server - kompiluje i uruchamia proces serwera,
        - make client - kompiluje i uruchamia proces klienta, jeśli żaden proces klienta nie zostal do tej pory uruchomiony,
        - ./client - uruchamia proces klienta, jeśli aktualnie jest juz uruchomiony inny proces klienta.

# Opis zawartosci plikow

    inf120573_s.c:
        W pliku zawarto kod odpowiadący za funkcjonalności związane z serwerem. Zaimplementowane funkcjonalności to:
            - tworzenie i usuwanie kolejek komunikatow do komunikacji miedzy serwerem, a klientem,
            - wczytywanie danych poczatkowych uzytkownikow z pliku,
            - obsluga i realizacja żądań zglaszanych przez klientow, takich jak:
                @ obsluga logowania i wylogowania,
                @ obsluga zapisu oraz wypisu z grupy,
                @ wymiana wiadomości między użytkownikiem, a użytkownikiem oraz między użytkownikiem, a grupą,
                @ obsluga żądań związanych z aktualnym czlonkostwem w grupie oraz aktualną liczbą zalogowanych użytkowników.

    inf120573_c.c:
        W pliku zawarto kod odpowiadający za funkcjonalności związane z klientem. Zaimplementowane funkcjonalności to:
            - interfejs umozliwiajacy poruszanie sie po komunikatorze oraz wysyłanie odpowiednich żądań do serwera, takich jak:
                @ zgłoszenie żądania logowania użytkownika legitymującego się określonym loginem i hasłem,
                @ zgłoszenie żądania pokazania aktualnego stanu zalogowanych użytkowników,
                @ zgłoszenie żądania wyświetlenia istniejących grup
                @ zgłoszenie ządania pokazania aktualnego stanu członków w poszczególnych grupach,
                @ zgłoszenie żądania zapisu lub wypisu z grupy
                @ zgłoszenie żądania wysłania wiadomości do poszczególnego użytkownika lub grupy
                @ zgłoszenie żądania odczytania wiadomości
                @ zgłoszenie żądania wylogowania się użytkownika

    Implementacja uzytych w powyższych plikach funkcji znajduje się w plikach nagłówkowych inf120573_serverFunction.h (serwer) oraz
    inf120573_clientFunction.h (klient). Implementacja użytych struktur danych znajduje się w pliku inf120573_struct.h.



