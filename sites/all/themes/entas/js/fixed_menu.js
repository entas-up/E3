$(window).scroll(function() {
				if ($(this).scrollTop() > 50) {
                    $('#navigation').addClass('fixed');
		        } else {
		            $('#navigation').removeClass('fixed');
		        }
		});