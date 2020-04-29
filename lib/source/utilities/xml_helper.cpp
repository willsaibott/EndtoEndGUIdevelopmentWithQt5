#include "xml_helper.h"

namespace cm {
namespace utilities {

QString XmlHelper::
to_string(const QDomNode &dom_node) {
  QString output;
  for (int ii = 0; ii < dom_node.childNodes().size(); ++ii) {
    auto sub_node{ dom_node.childNodes().at(ii) };
    append_node(sub_node, output);
  }
  return output;
}

void XmlHelper::
append_node(const QDomNode &dom_node, QString &output) {
  switch (dom_node.nodeType()) {
  case QDomNode::ElementNode:
    output.append("<").append(dom_node.nodeName());

    for (int ii = 0; ii < dom_node.attributes().size(); ++ii) {
      auto attr { dom_node.attributes().item(ii) };
      append_node(attr, output);
    }

    output.append(">");

    for (int ii = 0; ii < dom_node.childNodes().size(); ++ii) {
      auto child { dom_node.childNodes().at(ii) };
      append_node(child, output);
    }

    output.append("</" + dom_node.nodeName() + ">");
    break;
  case QDomNode::AttributeNode:
    output.append(" ")
          .append(dom_node.nodeName())
          .append("=\"")
          .append(dom_node.nodeValue())
          .append("\"");

    break;
  case QDomNode::TextNode:
    output.append(dom_node.nodeValue());
    break;
  default:
    break;
  }
}

}
}
