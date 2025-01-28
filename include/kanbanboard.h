#ifndef KANBANBOARD_H
#define KANBANBOARD_H

#include <vector>

#include "include/column.h"
#include "include/note.h"
#include "include/subtask.h"
#include "include/user.h"

using namespace std;

class KanbanBoard {
private:
    vector<Column> columns;
    vector<User*> users;
    User* currentUser;

public:
    KanbanBoard();
    KanbanBoard(const KanbanBoard&) = delete;
    KanbanBoard& operator=(const KanbanBoard&) = delete;

    static KanbanBoard& getInstance() {
        static KanbanBoard instance;
        return instance;
    }
    Column* getColumn(int index);
    void addTaskToColumn(int columnNumber, Task task);
    void deleteTaskFromColumn(int columnNumber, int taskIndex);
    void editTaskFromColumn(int columnNumber, int taskIndex, Task* editedTask);
    void moveTask(int sourceColumn, int taskIndex, int targetColumn);
    void addNote(Note note);
    void deleteNote(int noteIndex);
    void editNote(int noteIndex, Note* editedNote);
    void addSubtask(int taskIndex, int columnNumber, Subtask* subtask);
    void deleteSubtask(int taskIndex, int columnNumber, int subtaskIndex);
    Subtask* getSubtask(int taskIndex, int columnNumber, int subtaskIndex);
    void setCurrentUser(User* currentUser);
    User* getCurrentUser();
    User* getUser(QString username);
    void addUser(User newUser);
    bool authorizeUser(QString username, QString password);
};

#endif // KANBANBOARD_H
