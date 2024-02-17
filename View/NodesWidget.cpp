#include"NodesWidget.h"

NodesWidget::NodesWidget(Tree* t, QWidget* parent): QWidget(parent), tree(t){
  tree->attach(this);
  stack = new QStackedWidget();
  tree_widget = new TreeWidget(tree);
  search_query = new QLineEdit();
  search_button = new QPushButton("Search");
  results_widget = new ResultsWidget();
  QVBoxLayout* vbox = new QVBoxLayout(this);
  QHBoxLayout* searchbar = new QHBoxLayout();
  vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  searchbar->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

  searchbar->addWidget(search_query);
  searchbar->addStretch();
  searchbar->addWidget(search_button);
  searchbar->addStretch();
  vbox->addLayout(searchbar);

  stack->insertWidget(0, tree_widget);
  stack->insertWidget(1, results_widget);
  vbox->addWidget(stack);

  connect(search_button, &QPushButton::clicked, this, &NodesWidget::displaySearch);
  connect(results_widget, &ResultsWidget::selectedNode, this, &NodesWidget::searchResultSelected);
  connect(this, &NodesWidget::selectTreeNode, tree_widget, &TreeWidget::selectNode);
  connect(results_widget, &ResultsWidget::closePressed, this, &NodesWidget::closeResultsWidget);
  connect(tree_widget, &TreeWidget::leafSelected, this, &NodesWidget::leafSelect);
  connect(tree_widget, &TreeWidget::leafDeselected, this, &NodesWidget::leafDeselect);
}

void NodesWidget::closeResultsWidget(){
  stack->setCurrentIndex(0);
}

void NodesWidget::searchResultSelected(TreeNode* node){
  stack->setCurrentIndex(0);
  emit selectTreeNode(node);
}

void NodesWidget::displaySearch(){
  results_widget->addList(tree->search(search_query->text()));
  stack->setCurrentIndex(1);
}

void NodesWidget::observerUpdate(){
  QWidget::update();
}

void NodesWidget::leafSelect(BaseSensor* sensor){
  emit leafSelected(sensor);
}

void NodesWidget::leafDeselect(){
  emit leafDeselected();
}

TreeNode* NodesWidget::selected() const{
  return tree_widget->selected();
}