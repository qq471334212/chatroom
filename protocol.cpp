#include "protocol.h"
#include <QJsonDocument>
Protocol::Protocol()
    :type(none),len(0)
{

}

Protocol::Protocol(QByteArray &array)   //初始化数据包    拷贝构造函数
{
    this->len = *(int*)(array.data());
    this->type = *(Type*)(array.data()+sizeof (int));

    array = array.right(array.size() - headSize());//去掉头部的数据
    this->obj = QJsonDocument::fromJson(array.left(len)).object();
    array = array.right(array.size() - len);    //这里是包字节数据第一个包完全去掉
}

QPair<bool, Protocol> Protocol::unpack(QByteArray &array)   //判断包是否完整一个条数据
{
    if(array.size() < headSize()){return QPair<bool,Protocol>(false,Protocol());}
    if(array.size() < *(int*)(array.data()) + headSize()){return QPair<bool,Protocol>(false,Protocol());}

    return QPair<bool,Protocol>(true,Protocol(array));
}


QByteArray Protocol::toByteArray()  //发送时转换数据使用的
{
    QByteArray array(headSize(),0); //创建一个8个大小的字节数组,初始化为0
    QByteArray json = QJsonDocument(obj).toJson();  //发送时转换数据使用的

    this->len = json.size();

    memcpy(array.data(),&this->len,sizeof (int));
    memcpy(array.data()+sizeof (int),&this->type,sizeof (Type));

    return  array + json;
}

Protocol::Type Protocol::getType() const
{
    return type;
}

void Protocol::setType(const Type &value)
{
    type = value;
}

