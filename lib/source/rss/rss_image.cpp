#include "rss_image.h"
#include <QDomNode>

namespace cm {
namespace rss {


class RssImage::Implementation {
public:
  QString url;
  QString title;
  QString link;
  quint16 width;
  quint16 height;

  void
  update(const QDomNode& dom_node) {
    QDomElement image_url{ dom_node.firstChildElement("url") };
    QDomElement image_title{ dom_node.firstChildElement("title") };
    QDomElement image_link{ dom_node.firstChildElement("link") };
    QDomElement image_width{ dom_node.firstChildElement("width") };
    QDomElement image_height{ dom_node.firstChildElement("height") };

    if (!image_url.isNull()) {
      url = image_url.text();
    }
    if (!image_title.isNull()) {
      title = image_title.text();
    }
    if (!image_link.isNull()) {
      link = image_link.text();
    }
    width  = !image_width.isNull()  ? image_width.text().toUShort()  : 88;
    height = !image_height.isNull() ? image_height.text().toUShort() : 31;
  }
};

RssImage::
RssImage(QObject *parent, const QDomNode &dom_node)
  : QObject { parent }
{
  implementation.reset(new Implementation());
  implementation->update(dom_node);
}

RssImage::
~RssImage() {

}

const QString &RssImage::
link() const {
  return implementation->link;
}

const QString &RssImage::
title() const {
  return implementation->title;
}

const QString &RssImage::
url() const {
  return implementation->url;
}

quint16 RssImage::
width() const {
  return implementation->width;
}

quint16 RssImage::
height() const {
  return implementation->height;
}

}
}
