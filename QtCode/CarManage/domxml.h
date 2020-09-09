#ifndef DOMXML_H
#define DOMXML_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDomDocument>//文件
#include <QDomProcessingInstruction>//格式头部
#include <QDomElement>//元素

#include <QTextStream>//保存
#include <QDateTime>
#include <QDebug>
#define cout qDebug() << "{" << __FILE__ << ":" << __LINE__ << "}"

class DomXML
{
public:
    DomXML();

    //创建XML
    static void createXML(QString filePath);

    //追加结点到XML文档
    static void appendXML(QString filePath,QStringList ls);

    //写内容到XML文档
    static void writeXML(QDomDocument &doc,QDomElement &root,QStringList &ls);
};

#endif // DOMXML_H
