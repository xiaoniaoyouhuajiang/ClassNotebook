#pragma once

#include <QtCore/QObject>

#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include "MathOperationDataModel.hpp"
#include "DecimalData.hpp"
#include "TextData.hpp"

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AdditionModel : public MathOperationDataModel
{
public:

  virtual
  ~AdditionModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("Addition"); }

  QString
  name() const override
  { return QStringLiteral("Addition"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();
      _result = std::make_shared<DecimalData>(n1->number() +
                                              n2->number());
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};

//  -- - -- --  -  -- -

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class AdditionStringModel : public StringOperationDataModel
{
public:

  virtual
  ~AdditionStringModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("AdditionString"); }

  QString
  name() const override
  { return QStringLiteral("AdditionString"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();
      _result = std::make_shared<TextData>(n1->text() + n2->text());
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};

// - -- - - -- -- -  -- - -- -

//  -- - -- --  -  -- -

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ReverseStringModel : public StringOperationDataModel
{
public:

  virtual
  ~ReverseStringModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("ReverseString"); }

  QString
  name() const override
  { return QStringLiteral("ReverseString"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();

      QString s = n1->text() + n2->text();
      std::reverse(s.begin(), s.end());
      _result = std::make_shared<TextData>(s);
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};


// - -- - - - -- - -

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class RmSymbolStringModel : public StringOperationDataModel
{
public:

  virtual
  ~RmSymbolStringModel() {}

public:

  QString
  caption() const override
  { return QStringLiteral("RmSymbolString"); }

  QString
  name() const override
  { return QStringLiteral("RmSymbolString"); }

private:

  void
  compute() override
  {
    PortIndex const outPortIndex = 0;

    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();

      QString text = n1->text();
      text.replace(n2->text(), "");
      _result = std::make_shared<TextData>(text);
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }

    Q_EMIT dataUpdated(outPortIndex);
  }
};
