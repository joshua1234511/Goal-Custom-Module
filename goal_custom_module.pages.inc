<?php
function goal_custom_module_form($form, $form_state){
    $form = array();
    $form['name'] = array(
            '#type' => 'textfield',
            '#title' => 'name',
            '#attributes' => array(
            'class'=>array(''),
            'placeholder'=> 'Name',
        ),
        '#size' => 15,
        '#maxlength' => 128,
        '#title_display'=> 'invisible',
        '#required' => TRUE,
    );
    $form['email'] = array(
            '#type' => 'textfield',
            '#title' => 'email',
            '#attributes' => array(
            'class'=>array(''),
            'placeholder'=> 'Email',  
        ),
        '#size' => 15,
        '#maxlength' => 128,
        '#title_display'=> 'invisible',
        '#required' => TRUE,
        '#element_validate' => array('goal_custom_module_email_element_validate'),
    );
    $form['message'] = array(
            '#type' => 'textfield',
            '#title' => 'message',
            '#attributes' => array(
            'class'=>array(''),
            'placeholder'=> 'Message',
        ),
        '#size' => 15,
        '#maxlength' => 128,
        '#title_display'=> 'invisible',
        '#required' => TRUE,
    );

    // Form Submit button
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#attributes' => array(
            'class'=>array('btn1','form-submit'),
        ),
    );

    return $form;
}


function goal_custom_module_email_element_validate($element,$form, &$form_state){
    if (!valid_email_address($element['#value'])) {
        form_error($element, t('Please enter a valid email address.'));
    }
}

function goal_custom_module_form_submit($form, &$form_state){
    global $user;
    db_insert('goalcustommodule')
      ->fields(array(
        'created' => REQUEST_TIME,
        'uid' => $user->uid,
        'sid' =>  $user->sid,
        'name' => $form_state['values']['name'],
        'email' => $form_state['values']['email'],
        'message' => $form_state['values']['message'],
        'modified' => REQUEST_TIME,
      ))
      ->execute();
}

function goal_custom_module_form_input(){

    $output = '';

	$customer_support = drupal_get_form('goal_custom_module_form');

    $output.= render($customer_support);

    return $output;
	
}

function goal_custom_module_form_all(){


    $output = '';
    
	$result = goal_custom_module_form_all_data();
    if($result){
    	$output.='<table>';
    	foreach ($result as $value) {
    		$output.='<tr><td>'.$value->id.'</td><td>'.$value->name.'</td><td>'.$value->email.'</td><td>'.$value->message.'</td></tr>';
    	}
    	$output.='</table>';
    }

    return $output;
	
}

function goal_custom_module_form_all_data(){
	$list = db_query("SELECT * FROM {goalcustommodule} ")->fetchall();

	if ($list) {
    return $list;
  }

  return FALSE;
}
