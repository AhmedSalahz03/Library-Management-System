#include "StaffPage.h"

StaffPage::StaffPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	staffModel = new QSqlTableModel(this);
	staffModel->setTable("Librarians");
	staffModel->select();
	staffTableView = new QTableView(this);
	staffTableView->setParent(this); // Set the parent to the StaffPage widget
	staffTableView->setModel(staffModel);
	staffTableView->setGeometry(600, 20, 700, 400);
	staffTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

	staffFirstNameTF = new QLineEdit(this);
	staffFirstNameTF->move(20, 150);
	staffFirstNameTF->setPlaceholderText("First Name");
	staffLastNameTF = new QLineEdit(this);
	staffLastNameTF->move(20, 200);
	staffLastNameTF->setPlaceholderText("Last Name");
	staffEmailTF = new QLineEdit(this);
	staffEmailTF->move(20, 250);
	staffEmailTF->setPlaceholderText("Email");
	staffPhoneTF = new QLineEdit(this);
	staffPhoneTF->move(20, 300);
	staffPhoneTF->setPlaceholderText("Phone");
	staffStreetTF = new QLineEdit(this);
	staffStreetTF->move(20, 350);
	staffStreetTF->setPlaceholderText("Street");
	staffCityTF = new QLineEdit(this);
	staffCityTF->move(20, 400);
	staffCityTF->setPlaceholderText("City");
	staffZipcodeTF = new QLineEdit(this);
	staffZipcodeTF->move(20, 450);
	staffZipcodeTF->setPlaceholderText("Zipcode");
	staffSalaryTF = new QLineEdit(this);
	staffSalaryTF->move(20, 500);
	staffSalaryTF->setPlaceholderText("Salary");
	staffBranchIdTF = new QLineEdit(this);
	staffBranchIdTF->move(20, 550);
	staffBranchIdTF->setPlaceholderText("Branch ID");
	staffPasswordTF = new QLineEdit(this);
	staffPasswordTF->move(20, 600);
	staffPasswordTF->setPlaceholderText("Password");
	staffPasswordTF->setEchoMode(QLineEdit::Password);
	staffStartDateTF = new QDateEdit(this);
	staffStartDateTF->move(20, 650);
	staffStartDateTF->setDate(QDate::currentDate());


	addStaffBtn = new QPushButton("Add Staff", this);
	addStaffBtn->move(20, 700);
	deleteStaffBtn = new QPushButton("Delete Staff", this);
	deleteStaffBtn->move(200, 700);

	branchesModel = new QSqlTableModel(this);
	branchesModel->setTable("Branches");
	branchesModel->select();
	branchesTableView = new QTableView(this);
	branchesTableView->setParent(this); // Set the parent to the StaffPage widget
	branchesTableView->setModel(branchesModel);
	branchesTableView->setGeometry(600, 500, 700, 200);

	// Connect the Stylesheet File
	QFile styleFile("stylesheet.qss");
	if (styleFile.open(QFile::ReadOnly | QFile::Text)) {

		QString styleSheet = QLatin1String(styleFile.readAll());
		staffTableView->setStyleSheet(styleSheet);
		staffFirstNameTF->setStyleSheet(styleSheet);
		staffLastNameTF->setStyleSheet(styleSheet);
		staffEmailTF->setStyleSheet(styleSheet);
		staffPhoneTF->setStyleSheet(styleSheet);
		staffStreetTF->setStyleSheet(styleSheet);
		staffCityTF->setStyleSheet(styleSheet);
		staffZipcodeTF->setStyleSheet(styleSheet);
		staffSalaryTF->setStyleSheet(styleSheet);
		staffBranchIdTF->setStyleSheet(styleSheet);
		staffPasswordTF->setStyleSheet(styleSheet);
		staffStartDateTF->setStyleSheet(styleSheet);
		addStaffBtn->setStyleSheet(styleSheet);
		deleteStaffBtn->setStyleSheet(styleSheet);
		branchesTableView->setStyleSheet(styleSheet);

		styleFile.close();
	}
	connect(addStaffBtn, &QPushButton::clicked, this, &StaffPage::addStaff);
	connect(deleteStaffBtn, &QPushButton::clicked, [=]() {
		deleteSelectedRow(staffModel, staffTableView);
		});
	connect(staffModel, &QSqlTableModel::dataChanged, this, &StaffPage::handleDataChanged);
}

StaffPage::~StaffPage()
{}
void StaffPage::addStaff()
{

	QDate date = staffStartDateTF->date();

	QSqlQuery query;
	query.prepare("INSERT INTO Librarians (FirstName, LastName, Email, Phone, Street, City, Zipcode, Salary, BranchID, PasswordD, StartDate) VALUES (:FirstName, :LastName, :Email, :Phone, :Street, :City, :Zipcode, :Salary, :BranchId, :PasswordD, :StartDate)");
	query.bindValue(":FirstName", staffFirstNameTF->text());
	query.bindValue(":LastName", staffLastNameTF->text());
	query.bindValue(":Email", staffEmailTF->text());
	query.bindValue(":Phone", staffPhoneTF->text());
	query.bindValue(":Street", staffStreetTF->text());
	query.bindValue(":City", staffCityTF->text());
	query.bindValue(":Zipcode", staffZipcodeTF->text());
	query.bindValue(":Salary", staffSalaryTF->text());
	query.bindValue(":BranchId", staffBranchIdTF->text());
	query.bindValue(":PasswordD", staffPasswordTF->text());
	query.bindValue(":StartDate", date);
	
	if (query.exec()) {
		QMessageBox::information(this, "Success", "Staff added successfully");
		staffModel->select();
	}
	else {
		QMessageBox::information(this, "Error", "Failed to add staff");
	}
	staffModel->select();
	staffTableView->show();
}
void StaffPage::deleteSelectedRow(QSqlTableModel* tableModel, QTableView* tableView) {
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    // Check if there's at least one selected row
    if (!selectedRows.isEmpty()) {
        // Remove the first selected row
        tableModel->removeRow(selectedRows.first().row());
        // Refresh the model to reflect the changes
        tableModel->select();
    }

}
// Slot to handle the dataChanged signal
void StaffPage::handleDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
    // Check if the edited cell falls within the range of the dataChanged signal
    if (topLeft.isValid() && bottomRight.isValid()) {
        // Check if the edited cell is in the first column (column index 0)
        if (topLeft.column() == 12) {
            qDebug() << "Cell edited in the first column at row:" << topLeft.row();
            // Additional processing if needed

            // Refresh the table
            staffModel->select();
			staffTableView->show();
        }
    }
}
