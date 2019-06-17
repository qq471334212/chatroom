#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QJsonObject>
#include <QPair>
class Protocol{
public:
    enum Type{  //包类型
        none,
        regist,
        login,
        quit,
        chat,
        refreshUser,
        gift,
        newroom,
        goroom,
        topup,
        updatemoney,
        startLive,
        quitLive
    };
    Protocol();
    Protocol(QByteArray& array);
    static QPair<bool,Protocol> unpack(QByteArray& array);
    QJsonValue operator[](const QString& key)const{
        return obj[key];
    }
    QJsonValueRef operator[](const QString& key){
        return obj[key];
    }
    Type getType() const;
    void setType(const Type &value);

    QByteArray toByteArray();

    static inline int headSize(){
        return sizeof(int)+sizeof(Type);
    }

private:
    int len;
    Type type;
    QJsonObject obj;

};

#endif // PROTOCOL_H
