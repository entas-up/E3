CKEDITOR.plugins.add( 'clearfix', {
    icons: 'clearfix',
    init: function( editor ) {
        editor.addCommand( 'clearfix', {
            
                exec: function( editor ) {

                editor.insertHtml( '<div class="logo_clear">&nbsp;</div>' );
            }
        });
        editor.ui.addButton( 'clearfix', {
            label: 'Insert clearfix',
			icon : this.path + 'icons/clearfix.png',
            command: 'clearfix',
            toolbar: 'insert'
        });
    }
});