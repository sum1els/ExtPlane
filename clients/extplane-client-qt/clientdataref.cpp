#include "clientdataref.h"
#include "extplaneclient.h"

ClientDataRef::ClientDataRef() : QObject(nullptr)
  , m_accuracy(0)
  , m_subscribers(0)
  ,m_client(nullptr)
{
    m_values.reserve(1); // Always at least 1 size
}

ClientDataRef::ClientDataRef(QObject *parent, QString newName, double accuracy) : QObject(parent)
  , m_name(newName)
  , m_accuracy(accuracy)
  , m_subscribers(0)
  , m_client(nullptr) {
    m_values.reserve(1); // Always at least 1 size
}

QString& ClientDataRef::name() {
    return m_name;
}

void ClientDataRef::setName(QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

QString ClientDataRef::value()
{
    return m_values.isEmpty() ? "" : m_values.first();
}

ExtPlaneClient *ClientDataRef::client() const
{
    return m_client;
}

QStringList& ClientDataRef::values() {
    return m_values;
}

void ClientDataRef::updateValue(QString newValue) {
    if(!m_values.isEmpty() && newValue == m_values.first()) return;

    if(m_values.isEmpty()) {
        m_values.push_back(newValue);
    } else {
        m_values.replace(0, newValue);
    }
    emit changed(this);
}

void ClientDataRef::updateValue(QStringList &newValues) {
    if(newValues == m_values) return;
    m_values = newValues;
    emit changed(this);
}

double ClientDataRef::accuracy() {
    return m_accuracy;
}

int ClientDataRef::subscribers() {
    return m_subscribers;
}

void ClientDataRef::setSubscribers(int sub) {
    m_subscribers = sub;
}

void ClientDataRef::setValue(QString _newValue, int index) {
    if(m_values.size() < index + 1)
        m_values.reserve(index+1);
    m_values[index] = _newValue;
    emit valueSet(this);
}

void ClientDataRef::unsubscribe() {
    emit unsubscribed(this);
}


void ClientDataRef::setAccuracy(double accuracy)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_accuracy, accuracy))
        return;

    m_accuracy = accuracy;
    emit accuracyChanged(m_accuracy);
}

void ClientDataRef::setValues(QStringList values)
{
    if(values == m_values) return;
    m_values = values;
    emit changed(this);
}

void ClientDataRef::setClient(ExtPlaneClient *client)
{
    if (m_client == client)
        return;

    m_client = client;
    emit clientChanged(m_client);
}

void ClientDataRef::subscribeIfPossible()
{
    if(m_client && !m_name.isEmpty()) {
        m_client->subscribeDataRef(m_name, m_accuracy);
    }
}

bool ClientDataRef::isArray() {
    return m_values.size() > 1;
}
