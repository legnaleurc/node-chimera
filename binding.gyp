{
  'targets': [
    {
      'target_name': 'chimera',
      'sources': [
        'src/top.cc',
        'src/cookiejar.cc',
        'src/chimera.cc',
        'src/browser.cc'
      ],
      'conditions': [
        ['OS=="mac"', {
          'libraries': [
            '-F /usr/local/lib',
            '-framework AppKit',
            '-framework QtGui',
            '-framework QtCore',
            '-framework QtNetwork',
            '-framework QtWebKit'
          ],
        }],
        ['OS=="linux"', {
          'include_dirs': [
            '/usr/include/qt4'
          ],
          'libraries': [
            '-lQtCore',
            '-lQtGui',
            '-lQtNetwork',
            '-lQtWebKit'
          ],
        }]
      ]
    }
  ]
}
