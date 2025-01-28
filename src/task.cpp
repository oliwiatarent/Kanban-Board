#include "include/task.h"

Task::Task(QString title, QString description, QString priority, User* owner)
{
    this->id = 0;
    this->title = title;
    this->description = description;
    this->priority = priority;
    this->owner = owner;
}

void Task::setId(int id) {
    this->id = id;
}

void Task::setTitle(QString title) {
    this->title = title;
}

void Task::setDescription(QString description) {
    this->description = description;
}

void Task::setPriority(QString priority) {
    this->priority = priority;
}

int Task::getId() {
    return id;
}

QString Task::getTitle() {
    return title;
}

QString Task::getDescription() {
    return description;
}

QString Task::getPriority() {
    return priority;
}

User* Task::getOwner() {
    return owner;
}

void Task::addSubtask(Subtask* subtask) {
    subtasks.push_back(subtask);
}

Subtask* Task::getSubtask(int index) {
    return subtasks[index];
}

int Task::getNumberOfSubtasks() {
    return subtasks.size();
}

void Task::deleteSubtask(int subtaskIndex) {
    subtasks.erase(subtasks.begin() + subtaskIndex);
}
