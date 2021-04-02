<!DOCTYPE html>
<html>
    <head>
        <!-- Document Script -->
        <?php include "scripts/base.php"; ?>

        <!-- Document Style -->
        <link href="<?php echo ROOT; ?>/stylesheets/index.css" media=all rel="stylesheet"/>

        <!-- Document Title -->
        <title> Covenant University Undergraduate Online Application </title>
    </head>

    <body>
        <!-- Main -->
        <main>
            <!-- Hero -->
            <section class=no-select id=hero>
                <div role=container>
                    <h1 role=header> Welcome to </h1>
                    <h2 role=subheader> Covenant University Undergraduate Online Application </h2>
                </div>
            </section>

            <!-- Introduction -->
            <div id=introduction>
                <div class=warning>
                    <h1> Dear Prospective Student, </h1>

                    <p>
                        Admission into Covenant University is strictly by merit <br/>
                        <small> Admission Form is not opened for National (JAMB) students </small>
                    </p>
                </div>

                <small role=disclaimer> Before you apply, please read detailed information on academic programs, admission procedure and application deadlines in our admission website. </small>
            </div>

            <div id=application>
                <h1 class=no-select> Apply for Admission </h1>

                <p> Fresh applicants are required to create an account. Click <a href="<?php echo ROOT; ?>/pages/registration.php?state=signin">Here</a> to create an account. </p>
                <p>
                    If you already have an account, click <a href="<?php echo ROOT; ?>/pages/registration.php?state=login">Here</a> to login your credentials that will enable you complete your application over several sessions. <br/>
                    <span class=emphasis> The system will prompt you on how to complete the application. </span>
                </p>
            </div>

            <div id=status>
                <h1 class=no-select> Status of Application </h1>
                <p> After submission of your form, you can always check the status of your application by logging into the portal again. </p>
            </div>
        </main>
    </body>
</html>
