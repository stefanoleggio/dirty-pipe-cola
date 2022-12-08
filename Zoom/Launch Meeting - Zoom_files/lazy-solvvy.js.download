(function () {
  var LAZY_WIDGET_ID = 'solvvy-lazy-button';
  var LAZY_WIDGET_STYLES_ID = 'solvvy-lazy-button-styles';
  var FULL_INSTALL_SCRIPT = 'https://cdn.solvvy.com/deflect/customization/zoom/solvvy.js';
  var LAZY_URL_REGEXES = ['zoomdev\\.us/j', 'zoomdev\\.us/j/', 'zoomdev\\.us/join', 'zoomdev\\.us/s/', 'zoomdev\\.us/postattendee/', 'zoom\\.us/j', 'zoom\\.us/join/', 'zoom\\.us/s/', 'zoom\\.us/postattendee', 'zoom\\.us/postattendee/'];
  var ACTIVE_SOLVVY_COOKIE = '_slvforce';
  var ACTIVE_ADA_AB_TEST_COOKIE = '_slvabtestada';
  var SUCCESS_LOAD_EVENT = 'customization_initialized';
  var ERROR_EVENTS = [
    'modal_failed_to_load',
    'customization_failed_to_load',
    'ui_configuration_failed_to_load',
    'loader_aborted_incompatible_browser_detected'
  ];

  function getLazyWidget() {
    return document.getElementById(LAZY_WIDGET_ID);
  }

  function removeLazyWidget() {
    var widget = getLazyWidget();
    if (widget) {
      widget.remove();
    }
    var widgetStyles = document.getElementById(LAZY_WIDGET_STYLES_ID);
    if (widgetStyles) {
      widgetStyles.remove();
    }
  }

  function inAdaABTest() {
    return document.cookie.indexOf(`${ACTIVE_ADA_AB_TEST_COOKIE}=`) > -1;
  }

  function isAdaReady() {
    return (
      typeof window.adaEmbed === 'object' &&
      typeof window.adaEmbed.getInfo === 'function' &&
      typeof window.adaEmbed.toggle === 'function'
    );
  }

  function handleAda() {
    var interval = setInterval(function () {
      if (isAdaReady()) {
        removeLazyWidget();
        clearInterval(interval);
        try {
          window.adaEmbed.getInfo().then(function (data) {
            // data = { hasActiveChatter: boolean, hasClosedChat: boolean, isChatOpen: boolean, isDrawerOpen: boolean }
            if (!data.isDrawerOpen) {
              window.adaEmbed.toggle();
            }
          });
        } catch (e) {
          // do nothing
        }
      }
    }, 500);

    setTimeout(function () {
      if (!isAdaReady()) {
        removeLazyWidget();
        clearInterval(interval);
      }
    }, 10000);
  }

  function onLoadFullWidget() {
    if (inAdaABTest()) {
      handleAda();
    }
  }

  function loadFullWidget() {
    var solvvyScript = document.createElement('script');
    solvvyScript.type = 'text/javascript';
    solvvyScript.src = FULL_INSTALL_SCRIPT;
    document.body.appendChild(solvvyScript);
  }

  function getSolvvyLoadEvents() {
    try {
      var hist = window.Solvvy.stats.loadHistory;
      return typeof hist === 'object' ? hist : null;
    } catch (e) {
      return null;
    }
  }

  function onLazyWidgetClick() {
    loadFullWidget();
    setTimeout(function () {
      var widget = getLazyWidget();
      if (widget) {
        widget.innerHTML = `
<div class="svg-icon widget-icon">
  <div class="solvvy-loading"><div></div><div></div><div></div><div></div></div>
</div>
`;
      }
    }, 1000);

    var interval = setInterval(function () {
      var events = getSolvvyLoadEvents();
      if (events) {
        for (var i = 0; i < events.length; i++) {
          var event = events[i].event;
          if (event === SUCCESS_LOAD_EVENT) {
            onLoadFullWidget();
            clearInterval(interval);
            break;
          } else if (ERROR_EVENTS.indexOf(event) > -1) {
            onLoadFullWidget();
            if (!inAdaABTest()) {
              removeLazyWidget();
            }
            clearInterval(interval);
            break;
          }
        }
      }
    }, 100);

    // if after 30 seconds Solvvy has still not loaded
    setTimeout(function () {
      if (getLazyWidget()) {
        onLoadFullWidget();
        if (!inAdaABTest()) {
          removeLazyWidget();
        }
      }
      clearInterval(interval);
    }, 30000);
  }

  function addLazyWidgetStyles() {
    var cssText = `
.${LAZY_WIDGET_ID} {
  position: fixed;
  z-index: 1900000000;
  bottom: 0px;
  right: 0px;
  width: 60px;
  height: 60px;
  margin: 20px;
  padding: 12px;
  background: #0B5CFF;
  border-radius: 26px;
  box-shadow: 0px 0px 18px 3px rgb(0 0 0 / 35%);
  cursor: pointer;
  border: none;
}

.${LAZY_WIDGET_ID}:hover {
  background: #0050F0;
}

.${LAZY_WIDGET_ID} .solvvy-loading {
  display: inline-block;
  position: relative;
  width: 36px;
  height: 36px;
}
.${LAZY_WIDGET_ID} .solvvy-loading div {
  box-sizing: border-box;
  display: block;
  position: absolute;
  width: 36px;
  height: 36px;
  border: 4px solid #fff;
  border-radius: 50%;
  animation: solvvy-loading 1.2s cubic-bezier(0.5, 0, 0.5, 1) infinite;
  border-color: #fff transparent transparent transparent;
}
.${LAZY_WIDGET_ID} .solvvy-loading div:nth-child(1) {
  animation-delay: -0.45s;
}
.${LAZY_WIDGET_ID} .solvvy-loading div:nth-child(2) {
  animation-delay: -0.3s;
}
.${LAZY_WIDGET_ID} .solvvy-loading div:nth-child(3) {
  animation-delay: -0.15s;
}
@keyframes solvvy-loading {
  0% {
    transform: rotate(0deg);
  }
  100% {
    transform: rotate(360deg);
  }
}

#ada-entry {
  display: none !important;
}
`;

    var style = document.createElement('style');
    style.id = LAZY_WIDGET_STYLES_ID;
    style.appendChild(document.createTextNode(cssText));
    document.head.appendChild(style);
  }

  function addLazyWidget() {
    var widget = document.createElement('button');
    widget.id = LAZY_WIDGET_ID;
    widget.classList = LAZY_WIDGET_ID;
    widget.onclick = onLazyWidgetClick;
    widget.innerHTML = `
<div class="svg-icon widget-icon">
  <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 16 16">
    <mask height="16" width="14" y="0" x="1" maskUnits="userSpaceOnUse" style="mask-type:alpha" id="mask0_4_176">
      <path fill="#000001" d="M15 6.99999C15 3.10079 11.8118 -0.0538043 7.90011 0.000695695C4.18261 0.0524957 1.05229 3.1831 1.00069 6.9006C0.948592 10.6511 3.8468 13.7364 7.5226 13.984C7.7889 14.0019 8.00051 14.2098 8.00051 14.4766V15.4931C8.00051 15.8314 8.33412 16.0853 8.65322 15.973C12.3483 14.6725 15.0001 11.1399 15 6.99999ZM8.00011 3.49999C8.88411 3.49999 9.60012 4.2163 9.60012 5.1C9.60012 5.9837 8.88411 6.70001 8.00011 6.70001C7.11611 6.70001 6.40011 5.9837 6.40011 5.1C6.40011 4.2163 7.11611 3.49999 8.00011 3.49999ZM10.0421 10.4755C10.0151 10.4809 9.98811 10.4858 9.96111 10.4892C9.90811 10.4963 9.8551 10.4999 9.8001 10.4999H6.20009C5.53709 10.4999 5.00011 9.96279 5.00011 9.29989C5.00011 8.30579 6.20011 7.4999 8.00011 7.4999C9.10911 7.4999 9.9901 7.80579 10.5031 8.27279C10.8231 8.56429 11.0001 8.91809 11.0001 9.29989C11.0001 9.87979 10.5891 10.3637 10.0421 10.4755Z"></path>
    </mask>
    <g mask="url(#mask0_4_176)">
      <rect fill="#FFFFFF" height="16" width="16"></rect>
    </g>
  </svg>
</div>
`;
    widget.setAttribute('aria-label', 'Chat with bot');
    widget.setAttribute('title', 'Chat with bot');

    addLazyWidgetStyles();
    document.body.appendChild(widget);
  }

  function initLazyWidget() {
    // https://developers.solvvy.com/web-widget-api/getting-started#usage
    document.addEventListener('solvvy_ready', function () {
      removeLazyWidget();
      window.Solvvy.open();
    });

    addLazyWidget();
  }

  function lazyUrlMatches() {
    return LAZY_URL_REGEXES.reduce(function (launch, regex) {
      return new RegExp(regex).test(window.location.href) || launch;
    }, false);
  }

  function solvvyWFParamExists() {
    return window.location.href.indexOf('solvvyWF=') > -1;
  }

  function hasActiveSolvvySession() {
    return document.cookie.indexOf(`${ACTIVE_SOLVVY_COOKIE}=`) > -1;
  }

  function run() {
    if (!lazyUrlMatches() || solvvyWFParamExists() || hasActiveSolvvySession()) {
      loadFullWidget();
    } else {
      initLazyWidget();
    }
  }

  try {
    run();
  } catch (e) {
    loadFullWidget();
  }
})();
