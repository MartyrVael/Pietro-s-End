#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include"Tree/Tree.h"
#include"Reading/ReadingList.h"
#include"Reading/TableContainer.h"

class Environment{
private:
  Environment();
  static Environment* instance;
  Tree* tree_instance;
  ReadingList* readinglist_instance;
  TableContainer* tablecontainer_instance;
  QJsonObject toJson() const;
  bool fromJson(const QJsonObject& json);
  QJsonObject exportSection(TreeNode* node) const;
  bool importSection(const QJsonObject& json, TreeNode* parent);
public:
  ~Environment();
  static Environment* environment();
  Tree* tree() const;
  ReadingList* readinglist() const;
  TableContainer* tablecontainer() const;
  bool saveEnvironment(const QString& path) const;
  bool loadEnvironment(const QString& path);
  bool saveSection(TreeNode* head, const QString& path) const;
  bool loadSection(TreeNode* parent, const QString& path);
};

#endif