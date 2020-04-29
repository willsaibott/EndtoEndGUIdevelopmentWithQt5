#include "rss_channel.h"
#include <QtXml/QDomDocument>


namespace cm {
namespace rss {

class RssChannel::Implementation {
public:
  QString           description;
  RssImage*         image{ nullptr };
  QList<RssItem*>   items;
  QString           link;
  QString           title;

  void
  update(const QDomNode& dom_node) {
    QDomElement channel_description{ dom_node.firstChildElement("description") };
    QDomElement channel_link       { dom_node.firstChildElement("link")        };
    QDomElement channel_title      { dom_node.firstChildElement("title")       };

    if (!channel_description.isNull()) {
      description = channel_description.text();
    }

    if (!channel_link.isNull()) {
      link = channel_link.text();
    }

    if (!channel_title.isNull()) {
      title = channel_title.text();
    }
  }
};

RssChannel::
RssChannel(QObject *parent, const QDomNode &dom_node) : QObject (parent) {
  implementation.reset(new Implementation());
  implementation->update(dom_node);
}

RssChannel::
~RssChannel() {

}

void RssChannel::
add_item(RssItem *item) {
  if (!implementation->items.contains(item)) {
    item->setParent(this);
    implementation->items.push_back(item);
  }
}

const QString &RssChannel::
description() const {
  return implementation->description;
}

RssImage *RssChannel::
image() const {
  return implementation->image;
}

const QList<RssItem *> &RssChannel::
items() const {
  return implementation->items;
}

const QString &RssChannel::
link() const {
  return implementation->link;
}

void RssChannel::
set_image(RssImage *image) {
  if (implementation->image) {
    implementation->image->deleteLater();
    implementation->image = nullptr;
  }
  image->setParent(this);
  implementation->image = image;
}

const QString &RssChannel::
title() const {
  return implementation->title;
}

QQmlListProperty<RssItem> RssChannel::
ui_items() {
  return QQmlListProperty<RssItem>(this, implementation->items);
}

RssChannel *RssChannel::
from_xml(const QByteArray &xml_data, QObject *parent) {
  RssChannel* output { nullptr };
  QDomDocument doc;
  doc.setContent(xml_data);

  const auto channel_nodes = doc.elementsByTagName("channel");
  if (channel_nodes.size() == 1) {
    const auto image_nodes{ doc.elementsByTagName("image") };
    const auto item_nodes { doc.elementsByTagName("item")  };
    output = new RssChannel(parent, channel_nodes.at(0));

    if (image_nodes.size()) {
      output->set_image(new RssImage(output, image_nodes.at(0)));
    }

    for (int ii = 0; ii < item_nodes.size(); ++ii) {
      output->add_item(new RssItem(output, item_nodes.item(ii)));
    }
  }
  return output;
}

}
}
