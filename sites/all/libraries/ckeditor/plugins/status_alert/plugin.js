CKEDITOR.plugins.add( 'status_alert', {
    icons: 'alert',
    init: function( editor ) {
        editor.addCommand( 'status alert', {
            
                exec: function( editor ) {

                editor.insertHtml( '<div class="messages warning">&nbspЗамените&nbspтекст&nbspсообщения&nbsp</div>' );
            }
        });
        editor.ui.addButton( 'status alert', {
            label: 'Insert status alert',
			icon : this.path + 'icons/alert.png',
            command: 'status alert',
            toolbar: 'insert'
        });
    }
});