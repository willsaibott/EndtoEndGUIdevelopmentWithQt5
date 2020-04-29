#pragma once
#include <QUrl>
namespace cm {
namespace network {
class IWebRequest
{
public:
    IWebRequest(){}
    virtual ~IWebRequest(){}
    virtual void execute() = 0;
    virtual bool is_busy() const = 0;
    virtual void set_url(const QUrl& url) = 0;
    virtual QUrl url() const = 0;
};
}}
