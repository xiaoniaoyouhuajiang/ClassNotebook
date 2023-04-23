#include "TextSourceDataModel.hpp"

TextSourceDataModel::
TextSourceDataModel()
  : _lineEdit(new QLineEdit("Default Text"))
{
  connect(_lineEdit, &QLineEdit::textEdited,
          this, &TextSourceDataModel::onTextEdited);
}


unsigned int
TextSourceDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}

QJsonObject TextSourceDataModel::save() const {
  QJsonObject modelJson = NodeDataModel::save();

  if (!_lineEdit->text().isNull())
    modelJson["value"] = _lineEdit->text();
  else modelJson["value"] = "test";

  modelJson["type"] = "input";
  return modelJson;
}


void
TextSourceDataModel::
onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  Q_EMIT dataUpdated(0);
}


NodeDataType
TextSourceDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextSourceDataModel::
outData(PortIndex)
{
  return std::make_shared<TextData>(_lineEdit->text());
}

StringInitDataModel::
StringInitDataModel()
  : _lineEdit(new QLineEdit("Default Text"))
{
  connect(_lineEdit, &QLineEdit::textEdited,
          this, &StringInitDataModel::onTextEdited);
}


unsigned int
StringInitDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


QJsonObject StringInitDataModel::save() const {
  QJsonObject modelJson = NodeDataModel::save();

  if (!_lineEdit->text().isNull())
    modelJson["value"] = _lineEdit->text();
  else modelJson["value"] = "test";

  modelJson["type"] = "INIT_TYPE";
  return modelJson;
}

void
StringInitDataModel::
onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  Q_EMIT dataUpdated(0);
}


NodeDataType
StringInitDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
StringInitDataModel::
outData(PortIndex)
{
  return std::make_shared<TextData>(_lineEdit->text());
}
