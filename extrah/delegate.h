#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>
#include <QDebug>
#include <QComboBox>
#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QStyleOptionButton>
#include <QRect>
#include <QApplication>

class SpinBoxDelegate : public QItemDelegate//设置spinbox代理
{
    Q_OBJECT

public:
    SpinBoxDelegate(QObject *parent = 0):QItemDelegate(parent){}
    //返回一个编辑控件，用来编辑指定项的数据
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &,const QModelIndex &)const
    {
        //返回该QSpinBox控件
        QSpinBox *editor= new QSpinBox(parent);
        editor->setMinimum(0);
        editor->setMaximum(50);
        return editor;
    }
    void setEditorData(QWidget *editor,const QModelIndex &index)const
    {

        //获得当前模式中索引对应的数值
        int value = index.model()->data(index , Qt::EditRole).toInt();
        //强制类型转换
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        //设置spinbox的数值
        spinbox->setValue(value);

    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)const
    {
        QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
        //interpretText()用于解释spinbox中的文本。
        spinbox->interpretText();
        //获得编辑器中的数值
        int value = spinbox->value();
        model->setData(index,value,Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const
    {
        //根据给定的样式编辑器更新索引对应项
        editor->setGeometry(option.rect);
    }
};

class ReadOnlyDelegate : public QItemDelegate//设置只读代理
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        return NULL;
    }
};
class ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("系统管理员");
        editor->addItem("经理");
        editor->addItem("服务生");
        editor->addItem("厨师");
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class CheckBoxDelegate:public QItemDelegate //设置checkbox委托
{
    Q_OBJECT

public:
    CheckBoxDelegate(QObject *parent=0):QItemDelegate(parent){}
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
    {
            QCheckBox *editor=new QCheckBox(parent);
//            editor->installEventFilter(const_cast<CheckBoxDelegate*>(this));
            return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
            QString value=index.model()->data(index,Qt::CheckStateRole|Qt::DisplayRole).toString();
            QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
            checkBox->setCheckState(Qt::Unchecked);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
            QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
            QString value;
            if(checkBox->checkState() == Qt::Checked)
                value = "Y";
            else
                value = "N";
            model->setData(index, value);
    }
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
                editor->setGeometry(option.rect);
    }
};


#endif
