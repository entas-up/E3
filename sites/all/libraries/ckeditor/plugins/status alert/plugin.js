CKEDITOR.plugins.add( 'status alert', {
    icons: 'alert',
    init: function( editor ) {
        editor.addCommand( 'status alert', {
            
                exec: function( editor ) {

                editor.insertHtml( '<div class="messages warning">&nbsp</div>' );
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