/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * CatalogView.java
 *
 * Created on Aug 23, 2013, 12:22:26 AM
 */

/**
 *
 * @author Matt
 */
public class CatalogView extends javax.swing.JFrame {

    CatalogController controller = new CatalogController();
    /** Creates new form CatalogView */
    public CatalogView() {
        initComponents();
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        displayField = new javax.swing.JTextArea();
        titleLabel = new javax.swing.JLabel();
        sortYearButton = new javax.swing.JButton();
        sortTitleButton = new javax.swing.JButton();
        runtimeTextField = new javax.swing.JTextField();
        searchTitleButton = new javax.swing.JButton();
        removeButton = new javax.swing.JButton();
        yearTextField = new javax.swing.JTextField();
        searchCategoryButton = new javax.swing.JButton();
        categoryTextField = new javax.swing.JTextField();
        addButton = new javax.swing.JButton();
        titleTextField = new javax.swing.JTextField();
        priceTextField = new javax.swing.JTextField();
        editButton = new javax.swing.JButton();
        searchLabel = new javax.swing.JLabel();
        sortLabel = new javax.swing.JLabel();
        propertyLabel = new javax.swing.JLabel();
        saveButton = new javax.swing.JButton();
        loadButton = new javax.swing.JButton();
        clearButton = new javax.swing.JButton();
        searchLabel1 = new javax.swing.JLabel();
        searchLabel2 = new javax.swing.JLabel();
        searchLabel3 = new javax.swing.JLabel();
        searchLabel4 = new javax.swing.JLabel();
        searchLabel5 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        displayField.setColumns(20);
        displayField.setRows(5);
        jScrollPane1.setViewportView(displayField);

        titleLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        titleLabel.setText("MRT1");
        titleLabel.setToolTipText("");

        sortYearButton.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        sortYearButton.setText("Year");
        sortYearButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sortYearButtonActionPerformed(evt);
            }
        });

        sortTitleButton.setFont(new java.awt.Font("Tahoma", 0, 12));
        sortTitleButton.setText("Title");
        sortTitleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sortTitleButtonActionPerformed(evt);
            }
        });

        runtimeTextField.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        runtimeTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        runtimeTextField.setText("Runtime");

        searchTitleButton.setFont(new java.awt.Font("Tahoma", 0, 12));
        searchTitleButton.setText("Title");
        searchTitleButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchTitleButtonActionPerformed(evt);
            }
        });

        removeButton.setText("Remove");
        removeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removeButtonActionPerformed(evt);
            }
        });

        yearTextField.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        yearTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        yearTextField.setText("Year");

        searchCategoryButton.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        searchCategoryButton.setText("Category");
        searchCategoryButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchCategoryButtonActionPerformed(evt);
            }
        });

        categoryTextField.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        categoryTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        categoryTextField.setText("Category");

        addButton.setText("Add");
        addButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addButtonActionPerformed(evt);
            }
        });

        titleTextField.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        titleTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        titleTextField.setText("Title");

        priceTextField.setFont(new java.awt.Font("Tahoma", 0, 12)); // NOI18N
        priceTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        priceTextField.setText("Price");
        priceTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                priceTextFieldActionPerformed(evt);
            }
        });

        editButton.setText("Edit");
        editButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                editButtonActionPerformed(evt);
            }
        });

        searchLabel.setText("Title:");

        sortLabel.setText("Sort by :");

        propertyLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        propertyLabel.setText("Made by : Matt Phillips");

        saveButton.setFont(new java.awt.Font("Tahoma", 0, 12));
        saveButton.setText("Save");
        saveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                saveButtonActionPerformed(evt);
            }
        });

        loadButton.setFont(new java.awt.Font("Tahoma", 0, 12));
        loadButton.setText("Load");
        loadButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                loadButtonActionPerformed(evt);
            }
        });

        clearButton.setText("clear ");
        clearButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                clearButtonActionPerformed(evt);
            }
        });

        searchLabel1.setText("Search by :");

        searchLabel2.setText("Year:");

        searchLabel3.setText("Category:");

        searchLabel4.setText("Runtime:");

        searchLabel5.setText("Price:");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(128, 128, 128)
                        .addComponent(clearButton, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(titleLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 314, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(110, 110, 110)
                                .addComponent(sortLabel))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(61, 61, 61)
                                .addComponent(saveButton)
                                .addGap(4, 4, 4)
                                .addComponent(loadButton))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(19, 19, 19)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                        .addGap(23, 23, 23)
                                        .addComponent(propertyLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 175, Short.MAX_VALUE))
                                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                            .addComponent(searchLabel2)
                                            .addComponent(searchLabel4)
                                            .addComponent(searchLabel5)
                                            .addComponent(searchLabel3)
                                            .addComponent(searchLabel))
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                            .addGroup(layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                    .addComponent(searchCategoryButton, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                    .addComponent(sortYearButton))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 42, Short.MAX_VALUE)
                                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                    .addComponent(searchTitleButton)
                                                    .addComponent(sortTitleButton)))
                                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                    .addComponent(priceTextField, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                                                    .addComponent(runtimeTextField, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                                                    .addComponent(yearTextField, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                                                    .addComponent(categoryTextField, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE)
                                                    .addComponent(titleTextField, javax.swing.GroupLayout.DEFAULT_SIZE, 174, Short.MAX_VALUE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)))))
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addGap(26, 26, 26)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                            .addComponent(addButton)
                                            .addComponent(editButton)))
                                    .addGroup(layout.createSequentialGroup()
                                        .addGap(18, 18, 18)
                                        .addComponent(removeButton)))))
                        .addGap(18, 18, 18)
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 314, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(16, Short.MAX_VALUE))
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                    .addGap(107, 107, 107)
                    .addComponent(searchLabel1)
                    .addContainerGap(527, Short.MAX_VALUE)))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(titleLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 22, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(clearButton, javax.swing.GroupLayout.PREFERRED_SIZE, 14, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 341, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(searchLabel)
                            .addComponent(titleTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(addButton)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(categoryTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(searchLabel3)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(yearTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(editButton, javax.swing.GroupLayout.PREFERRED_SIZE, 23, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(searchLabel2))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(removeButton)
                            .addComponent(runtimeTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(searchLabel4))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(priceTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 21, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(searchLabel5))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(20, 20, 20)
                                .addComponent(searchCategoryButton))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(21, 21, 21)
                                .addComponent(searchTitleButton)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(sortLabel)
                        .addGap(9, 9, 9)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(sortTitleButton)
                            .addComponent(sortYearButton))
                        .addGap(44, 44, 44)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(saveButton)
                            .addComponent(loadButton))
                        .addGap(18, 18, 18)
                        .addComponent(propertyLabel)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                    .addContainerGap(180, Short.MAX_VALUE)
                    .addComponent(searchLabel1)
                    .addGap(197, 197, 197)))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void priceTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_priceTextFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_priceTextFieldActionPerformed

    private void sortYearButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sortYearButtonActionPerformed
        controller.UCsortByYear();
        displayField.setText("Collection has been sorted by Year");
        System.out.println("sort complete.");
        String result = "";
        DVDModel temp = new DVDModel();
        result = controller.toString();
        displayField.setText(result);

        // TODO add your handling code here:
    }//GEN-LAST:event_sortYearButtonActionPerformed

    private void saveButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_saveButtonActionPerformed
       controller.UCwriteCollection();
       displayField.setText("Collection saved.");
        // TODO add your handling code here:
    }//GEN-LAST:event_saveButtonActionPerformed

    private void loadButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_loadButtonActionPerformed
       controller.UCloadCollection();
       displayField.setText("Collection loaded.");
       // TODO add your handling code here:
    }//GEN-LAST:event_loadButtonActionPerformed

    private void sortTitleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_sortTitleButtonActionPerformed
        controller.UCsortByTitle();
        displayField.setText("Collection has been sorted by Title");
        System.out.println("sort complete.");
        String result = "";
        result = controller.toString();
        displayField.setText(result);
        // TODO add your handling code here:
    }//GEN-LAST:event_sortTitleButtonActionPerformed

    private void searchCategoryButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchCategoryButtonActionPerformed
        String theCategory = yearTextField.getText();
        String result = controller.UClistByCategory(theCategory);
        displayField.setText(result);
        clearInput();
        // TODO add your handling code here:
    }//GEN-LAST:event_searchCategoryButtonActionPerformed

    private void searchTitleButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchTitleButtonActionPerformed
       String theTitle = titleTextField.getText();
       String result = controller.UClookupByTitle(theTitle).toString();
       displayField.setText(result);
       clearInput();
        // TODO add your handling code here:
    }//GEN-LAST:event_searchTitleButtonActionPerformed

    private void removeButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_removeButtonActionPerformed
       String remove = titleTextField.getText();
       int result = controller.UCremoveDVD(remove);
       if (result >=0)
           displayField.setText("DVD : " + remove + " has been removed");
       else
           displayField.setText("DVD was not found by the title : " + remove);
       clearInput();
       // TODO add your handling code here:
    }//GEN-LAST:event_removeButtonActionPerformed

    private void addButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_addButtonActionPerformed
        String theTitle = titleTextField.getText();
        String theCategory = yearTextField.getText();
        String theYear = categoryTextField.getText();
        String theRuntime = priceTextField.getText();
        String thePrice = runtimeTextField.getText();
        DVDModel newDVD = new DVDModel(theTitle, theCategory, theYear, theRuntime, thePrice);
        boolean result = controller.UCaddDVD(newDVD);
        if (result)
            displayField.setText("DVD added. \n" + newDVD.toString());
        else
            displayField.setText("DVD could not be added.");
        clearInput();
        // TODO add your handling code here:
    }//GEN-LAST:event_addButtonActionPerformed

    private void editButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_editButtonActionPerformed
      
        String theTitle = titleTextField.getText();
        String theCategory = yearTextField.getText();
        String theYear = categoryTextField.getText();
        String theRuntime = priceTextField.getText();
        String thePrice = runtimeTextField.getText();
        DVDModel newInfo = new DVDModel(theTitle, theCategory, theYear, theRuntime, thePrice);

        if (controller.UClookupByTitle(theTitle) != null)
        {
            controller.UCeditDVD(theTitle, newInfo);
            
            displayField.setText("DVD edited to : " + newInfo.toString());
        }
        else
            displayField.setText("DVD could not be edited.");
        clearInput();
        // TODO add your handling code here:
    }//GEN-LAST:event_editButtonActionPerformed

    private void clearButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_clearButtonActionPerformed
        clearInput();
        // TODO add your handling code here:
    }//GEN-LAST:event_clearButtonActionPerformed

    private void clearInput()
    {
        titleTextField.setText("");
        yearTextField.setText("");
        categoryTextField.setText("");
        priceTextField.setText("");
        runtimeTextField.setText("");
    }

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new CatalogView().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton addButton;
    private javax.swing.JTextField categoryTextField;
    private javax.swing.JButton clearButton;
    private javax.swing.JTextArea displayField;
    private javax.swing.JButton editButton;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JButton loadButton;
    private javax.swing.JTextField priceTextField;
    private javax.swing.JLabel propertyLabel;
    private javax.swing.JButton removeButton;
    private javax.swing.JTextField runtimeTextField;
    private javax.swing.JButton saveButton;
    private javax.swing.JButton searchCategoryButton;
    private javax.swing.JLabel searchLabel;
    private javax.swing.JLabel searchLabel1;
    private javax.swing.JLabel searchLabel2;
    private javax.swing.JLabel searchLabel3;
    private javax.swing.JLabel searchLabel4;
    private javax.swing.JLabel searchLabel5;
    private javax.swing.JButton searchTitleButton;
    private javax.swing.JLabel sortLabel;
    private javax.swing.JButton sortTitleButton;
    private javax.swing.JButton sortYearButton;
    private javax.swing.JLabel titleLabel;
    private javax.swing.JTextField titleTextField;
    private javax.swing.JTextField yearTextField;
    // End of variables declaration//GEN-END:variables

}
