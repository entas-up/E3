CKEDITOR.plugins.add( 'status_error', {
    icons: 'error',
    init: function( editor ) {
        editor.addCommand( 'status error', {
            
                exec: function( editor ) {

                editor.insertHtml( '<div class="messages error">&nbsp</div>' );
            }
        });
        editor.ui.addButton( 'status error', {
            label: 'Insert status error',
			icon : this.path + 'icons/error.png',
            command: 'status error',
            toolbar: 'insert'
        });
    }
});