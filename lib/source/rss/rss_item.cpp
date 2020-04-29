#include "rss_item.h"
#include <utilities/xml_helper.h>

namespace cm {
namespace rss {

using namespace utilities;

class RssItem::Implementation {
public:
  Implementation(RssItem* item)
    : _item{ item }
  {

  }

  RssItem*   _item{ nullptr };
  QString    _description;
  QString    _link;
  QDateTime  _pub_date;
  QString    _title;

  void
  update(const QDomNode& dom_node) {
    const auto item_link   { dom_node.firstChildElement("link") };
    const auto item_pubdate{ dom_node.firstChildElement("pubDate") };
    const auto item_title  { dom_node.firstChildElement("title") };
    for (int ii = 0; ii < dom_node.childNodes().size(); ++ii) {
      QDomNode child_node = dom_node.childNodes().at(ii);
      if (child_node.nodeName() == "description") {
        _description = XmlHelper::to_string(child_node);
      }
    }

    if (!item_link.isNull()) {
      _link = item_link.text();
    }

    if (!item_pubdate.isNull()) {
      _pub_date = QDateTime::fromString(item_pubdate.text(), Qt::RFC2822Date);
    }

    if (!item_title.isNull()) {
      _title = item_title.text();
    }
  }

};

RssItem::
RssItem(QObject *parent, const QDomNode &dom_node) : QObject (parent) {
  implementation.reset(new Implementation(this));
  implementation->update(dom_node);
}

RssItem::
~RssItem() {

}

const QString &RssItem::
description() const {
  return implementation->_description;
}

const QString &RssItem::
link() const {
  return implementation->_link;
}

const QDateTime &RssItem::
pub_date() const {
  return implementation->_pub_date;
}

const QString &RssItem::
title() const {
  return implementation->_title;
}

}
}
