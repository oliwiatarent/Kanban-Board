#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    QString firstName;
    QString secondName;
    QString username;
    QString password;

public:
    User(QString firstName, QString secondName, QString username, QString password);
    QString getFirstName();
    QString getSecondName();
    QString getUsername();
    QString getPassword();
    void setFirstName(QString firstName);
    void setSecondName(QString secondName);
    void setUsername(QString username);
    void setPassword(QString password);
};

#endif // USER_H
