#include "include/user.h"

User::User(QString firstName, QString secondName, QString username, QString password) {
    this->firstName = firstName;
    this->secondName = secondName;
    this->username = username;
    this->password = password;
}

QString User::getFirstName() {
    return firstName;
}

QString User::getSecondName() {
    return secondName;
}

QString User::getUsername() {
    return username;
}

QString User::getPassword() {
    return password;
}

void User::setFirstName(QString firstName) {
    this->firstName = firstName;
}

void User::setSecondName(QString secondName) {
    this->secondName = secondName;
}

void User::setUsername(QString username) {
    this->username = username;
}

void User::setPassword(QString password) {
    this->password = password;
}

