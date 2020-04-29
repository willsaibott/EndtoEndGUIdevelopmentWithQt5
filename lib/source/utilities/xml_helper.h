#pragma once

#include <QDomNode>
#include <QString>

#include <lib_global.h>

namespace cm {
namespace utilities {

class CMLIBSHARED_EXPORT XmlHelper
{
public:
    static QString to_string(const QDomNode& domNode);
private:
    XmlHelper(){}
    static void append_node(const QDomNode& domNode, QString& output);
};

}
}

