#include "include/kanbanboard.h"

KanbanBoard::KanbanBoard() {
    columns.push_back(Column("To do"));
    columns.push_back(Column("In progress"));
    columns.push_back(Column("Done"));
    columns.push_back(Column("Notes"));

    users.push_back(new User("Użytkownik", "User", "user", "user"));
    users.push_back(new User("Jan", "Kowalski", "jankowalski", "jan"));
    users.push_back(new User("Karol", "Nowak", "knowak", "karol"));
    users.push_back(new User("Natalia", "Wiśniewska", "nwisniewska", "nwis"));

    Task task1("Raport", "Stworzenie szczegółowego raportu finansowego za ostatni kwartał.", "Wysoki", users[2]);
    Subtask* subtask1 = new Subtask("Zbierz dane z działu sprzedaży.", "Wysoki");
    Subtask* subtask2 = new Subtask("Zweryfikuj dane z działem księgowości.", "Średni");
    Subtask* subtask3 = new Subtask("Przygotuj wykresy i wizualizacje.", "Wysoki");
    addTaskToColumn(0, task1);
    addSubtask(0, 0, subtask1);
    addSubtask(0, 0, subtask2);
    addSubtask(0, 0, subtask3);

    Task task2("Aktualizacja strony internetowej", "Dodanie nowych zdjęć do galerii oraz zmiana opisu w sekcji \"O Nas\".", "Niski", users[1]);
    Subtask* subtask4 = new Subtask("Przygotuj nowy tekst do sekcji \"O nas\".", "Niski");
    subtask4->setDone(true);
    Subtask* subtask5 = new Subtask("Wybierz zdjęcia do udostępnienia w galerii.", "Średni");
    subtask5->setDone(true);
    addTaskToColumn(2, task2);
    addSubtask(0, 2, subtask4);
    addSubtask(0, 2, subtask5);


    Task task3("Organizacja spotkania zespołu", "Zorganizowanie miesięcznego spotkania zespołu w celu omówienia wyników pracy i planów na przyszłość.", "Średni", users[2]);
    Subtask* subtask6 = new Subtask("Zarezerwuj salę konferencyjną.", "Średni");
    subtask6->setDone(true);
    Subtask* subtask7 = new Subtask("Wyślij zaproszenia do wszystkich członków zespołu.", "Średni");
    Subtask* subtask8 = new Subtask("Przygotuj prezentację podsumowującą wyniki.", "Niski");
    addTaskToColumn(1, task3);
    addSubtask(0, 1, subtask6);
    addSubtask(0, 1, subtask7);
    addSubtask(0, 1, subtask8);


    Task task4("Kampania marketingowa", "Stworzenie treści i grafik do nowej kampanii marketingowej w mediach społecznościowych.", "Niski", users[2]);
    Subtask* subtask9 = new Subtask("Stwórz grafiki promocyjne.", "Średni");
    Subtask* subtask10 = new Subtask("Opracuj koncepcje kampanii.", "Wysoki");
    subtask10->setDone(true);
    Subtask* subtask11 = new Subtask("Zaplanuj harmonogram publikacji.", "Niski");
    addTaskToColumn(1, task4);
    addSubtask(1, 1, subtask9);
    addSubtask(1, 1, subtask10);
    addSubtask(1, 1, subtask11);

    Task task5("Rekrutacja pracowników", "Przeprowadzenie procesu rekrutacyjnego na stanowisko koordynatora projektów w celu uzupełnienia braków kadrowych i wzmocnienia zespołu.", "Niski", users[3]);
    Subtask* subtask12 = new Subtask("Przygotuj i opublikuj ogłoszenie o pracę na portalach rekrutacyjnych i stronie firmowej.", "Wysoki");
    Subtask* subtask13 = new Subtask("Skontaktuj się z wybranymi kandydatami i zaplanuj rozmowy kwalifikacyjne.", "Wysoki");
    Subtask* subtask14 = new Subtask("Wybierz najlepszego kandydata i przygotuj ofertę pracy.", "Wysoki");
    addTaskToColumn(0, task5);
    addSubtask(1, 0, subtask12);
    addSubtask(1, 0, subtask13);
    addSubtask(1, 0, subtask14);

    addNote(Note("Pomysł na nowy produkt", "Rozważenie wprowadzenia ekologicznych opakowań dla naszych produktów. Klienci coraz częściej pytają o rozwiązania proekologiczne, co może zwiększyć naszą przewagę konkurencyjną.", "#c7f9ff", users[3]));
    addNote(Note("Feedback od klientów", "Otrzymaliśmy liczne sugestie dotyczące ulepszenia naszej aplikacji mobilnej, m.in. lepsza nawigacja, możliwość personalizacji interfejsu oraz szybsze ładowanie.", "#ebcbf5", users[1]));
}

Column* KanbanBoard::getColumn(int index) {
    return &columns[index];
}

void KanbanBoard::addTaskToColumn(int columnNumber, Task task) {
    if (columnNumber >= 0 && columnNumber <= static_cast<int>(columns.size())) {
        columns[columnNumber].addTask(task);
    }
}

void KanbanBoard::deleteTaskFromColumn(int columnNumber, int taskIndex) {
    if (columnNumber >= 0 && columnNumber <= static_cast<int>(columns.size())) {
        columns[columnNumber].deleteTask(taskIndex);
    }
}

void KanbanBoard::editTaskFromColumn(int columnNumber, int taskIndex, Task* editedTask) {
    if (columnNumber >= 0 && columnNumber <= static_cast<int>(columns.size())) {
        columns[columnNumber].editTask(taskIndex, editedTask);
    }
}

void KanbanBoard::moveTask(int sourceColumn, int taskIndex, int targetColumn) {
    Column* source = getColumn(sourceColumn);
    Column* target = getColumn(targetColumn);
    Task* taskPointer =  source->getTask(taskIndex);
    Task newTask = *taskPointer;
    source->deleteTask(taskIndex);
    target->addTask(newTask);
}

void KanbanBoard::addNote(Note note) {
    columns[3].addNote(note);
}

void KanbanBoard::deleteNote(int noteIndex) {
    columns[3].deleteNote(noteIndex);
}

void KanbanBoard::editNote(int noteIndex, Note* editedNote) {
    columns[3].editNote(noteIndex, editedNote);
}

void KanbanBoard::addSubtask(int taskIndex, int columnNumber, Subtask* subtask) {
    columns[columnNumber].getTask(taskIndex)->addSubtask(subtask);
}

void KanbanBoard::deleteSubtask(int taskIndex, int columnNumber, int subtaskIndex) {
    columns[columnNumber].getTask(taskIndex)->deleteSubtask(subtaskIndex);
}

Subtask* KanbanBoard::getSubtask(int taskIndex, int columnNumber, int subtaskIndex) {
    return columns[columnNumber].getTask(taskIndex)->getSubtask(subtaskIndex);
}

void KanbanBoard::setCurrentUser(User* currentUser) {
    this->currentUser = currentUser;
}

User* KanbanBoard::getCurrentUser() {
    return currentUser;
}

User* KanbanBoard::getUser(QString username) {
    for (User* user : users) {
        if (user->getUsername() == username)
            return user;
    }
    return nullptr;
}

void KanbanBoard::addUser(User newUser) {
    users.push_back(new User(newUser.getFirstName(), newUser.getSecondName(), newUser.getUsername(), newUser.getPassword()));
}

bool KanbanBoard::authorizeUser(QString username, QString password) {
    for (User* user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            return true;
        }
    }
    return false;
}

